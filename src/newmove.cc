#include <ncurses.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "int_to_str.hh"
#include "newmove.hh"
#include "show_message.hh"

int from_visual(const std::string& cont, int x) {
    int count = 0,
        til = 0;
    for(int i = 0; i < cont.length(); i++) {
        int len;
        if(cont[i] == '\t') {
            len = TAB_SIZE() - 1 - til;
            til = 0;
        } else {
            len = 1;
            til++;
            til %= TAB_SIZE();
        }
        count += len;
        if(count >= x) {
            return i;
        }
    }
}

int to_visual(const std::string& cont, int x) {
    int til = 0,
        xx = -1;
    for(std::string::const_iterator i = cont.begin();
                i <= cont.begin() + x; i++) {
        if(*i == '\t') {
            xx += TAB_SIZE() - til;
            til = 0;
        } else {
            til++;
            til %= TAB_SIZE();
            xx++;
        }
    }
    return xx;
}

void redrawyx(contents& contents) {
    move(contents.y,to_visual((*contents.cont)[contents.y],contents.x));
}

void mvline(contents& contents, unsigned long line) {
    mvrel(contents, line - contents.y, 0);
}
void mv(contents& contents, unsigned long _y, unsigned long _x) {
    mvrel(contents, _y - contents.y, _x - contents.x);
}

void mvrel(contents& contents, long y, long x) {
    if(y < 0) mvu(contents,-y);
    else      mvd(contents, y);
    if(x < 0) mvb(contents,-x);
    else      mvf(contents, x);
}

void mvcol(contents& contents, unsigned long col) {
    unsigned int len = (*contents.cont)[contents.y].length();
    if(len >= col) {
        contents.x = col;
        contents.waiting_for_desired = false;
    } else {
        show_message((std::string("Can't move to column: ")
                      + int_to_str(col)).c_str());
    }
    redrawyx(contents);
}

void mvsot(contents& contents) {
    mvsol(contents);
    const std::string& str = (*contents.cont)[contents.y];
    for(unsigned int i = 0; i < str.length(); i++)
        if(str[i] == ' ' || str[i] == '\t') mvf(contents);
        else break;
}

void mveol(contents& contents) {
    mvcol(contents,(*contents.cont)[contents.y].length() - 1);
}
void mvsol(contents& contents) { mvcol(contents,0); }

void mvsop(contents& contents) {
    contents.y = 0;
    contents.x = 0;
    contents.waiting_for_desired = false;
    redrawyx(contents);
}
void mveop(contents& contents) {
    contents.y = contents.cont->size();
    contents.x = 0;
    contents.waiting_for_desired = false;
    redrawyx(contents);
}

void mvd(contents& contents, long times) {
    if(contents.y + times < 0 || contents.y + times >= contents.cont->size()) {
        show_message("Can't move to that location (start/end of buffer)");
        return;
    }
    int vis = to_visual((*contents.cont)[contents.y],contents.x);
    contents.y += times;
    unsigned int len = (*contents.cont)[contents.y].length();
    if(contents.waiting_for_desired) {
        if(contents.x >= len) {
            contents.x = len - 1;
        } else if(contents.desired_x > contents.x
                  && contents.desired_x < len) {
            // x  desired  len
            contents.x = contents.desired_x;
            contents.waiting_for_desired = false;
        } else {
            // x  len  desired
            contents.x = len - 1;
        }
    } else if(len <= contents.x) {
        contents.waiting_for_desired = true;
        contents.desired_x = contents.x;
        contents.x = len - 1;
    } else {
        //visually adjust x
        //int vis = to_visual((*contents.cont)[contents.y],contents.x);
        contents.x = from_visual((*contents.cont)[contents.y],vis);
    }
    contents.x = contents.x >= 0 ? contents.x : 0;
    redrawyx(contents);
}
void mvu(contents& contents, long times) { mvd(contents,-times); }


static bool isDeliminator(char ch) {
    for(unsigned int i = 0; i < DELIMINATORS().length(); i++)
        if(DELIMINATORS()[i] == ch) return true;
    return false;
}
void mvfw(contents& contents,unsigned long words) {
}
void mvbw(contents& contents,unsigned long words) {
}


inline static unsigned int fixLen(unsigned int len) {
    return len ? len : 1;
}
void mvf(contents& contents, unsigned long times) {
    long newx = contents.x + times;
    try {
        while(fixLen(contents.cont->at(contents.y).length()) <= newx) {
            newx -= fixLen((*contents.cont)[contents.y].length());
            contents.y++;
        }
    } catch(...) { }
    if(contents.y >= contents.cont->size()) contents.y = contents.cont->size()-1;
    if(contents.x < 0) contents.x = 0;
    else      contents.x = newx;
    show_message((std::string("for (x,y): (") + int_to_str(contents.x)
                  + "," + int_to_str(contents.y) + ")").c_str());
    contents.waiting_for_desired = false;
    redrawyx(contents);
}
void mvb(contents& contents, unsigned long times) {
    long newx = contents.x - times;
    while(newx < 0) {
        try {
            contents.y--;
            newx += fixLen(contents.cont->at(contents.y).length());
        } catch(...) {
            break;
        }
    }
    if(contents.y < 0) contents.y = 0;
    if(contents.x < 0) contents.x = 0;
    else      contents.x = newx;
    show_message((std::string("back (x,y): (") + int_to_str(contents.x)
                  + "," + int_to_str(contents.y) + ")").c_str());
    contents.waiting_for_desired = false;
    redrawyx(contents);
}
