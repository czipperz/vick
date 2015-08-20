#include <ncurses.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "int_to_str.hh"
#include "newmove.hh"
#include "show_message.hh"

typedef std::vector<std::string>* contents;

static long
    y = 0,x = 0,
    desired_x;
static bool waiting_for_desired;

static int to_visual(const std::string& cont, int x) {
    int til = 0,
        xx = 0;
    for(std::string::const_iterator i = cont.begin();
                                    i < cont.begin() + x; i++) {
        if(*i == '\t') {
            xx += TAB_SIZE() - 1 - til;
            if(xx > x) return xx;
            til = 0;
        } else {
            til++;
            til %= TAB_SIZE();
            xx++;
        }
    }
    return xx;
}

static void redrawyx(contents contents) {
    move(y,to_visual((*contents)[y],x));
}

void mvline(contents contents, unsigned long line) {
    mvrel(contents, line - y, 0);
}
void mv(contents contents, unsigned long _y, unsigned long _x) {
    mvrel(contents, _y - y, _x - x);
}

void mvrel(contents contents, long y, long x) {
    if(y < 0) mvu(contents,-y);
    else      mvd(contents, y);
    if(x < 0) mvb(contents,-x);
    else      mvf(contents, x);
}

void mvcol(contents contents, unsigned long col) {
    unsigned int len = (*contents)[y].length();
    if(len >= col) {
        x = col;
        waiting_for_desired = false;
    } else {
        show_message((std::string("Can't move to column: ")
                      + int_to_str(col)).c_str());
    }
    redrawyx(contents);
}

void mvsot(contents contents) {
    mvsol(contents);
    const std::string& str = (*contents)[y];
    for(unsigned int i = 0; i < str.length(); i++)
        if(str[i] == ' ' || str[i] == '\t') mvf(contents);
        else break;
}

void mveol(contents contents) {
    mvcol(contents,(*contents)[y].length() - 1);
}
void mvsol(contents contents) { mvcol(contents,0); }

void mvsop(contents contents) {
    y = 0;
    x = 0;
    redrawyx(contents);
}
void mveop(contents contents) {
    y = contents->size();
    x = 0;
    redrawyx(contents);
}

void mvd(contents contents, long times) {
    std::vector<std::string> cont = *contents;
    if(y + times < 0 || y + times >= cont.size()) {
        show_message("Can't move to that location (start/end of buffer)");
        return;
    }
    y += times;
    unsigned int len = cont[y].length();
    if(waiting_for_desired) {
        if(x >= len) {
            x = len - 1;
        } else if(desired_x >= x) {
            waiting_for_desired = false;
            x = desired_x;
        } else {
            
        }
    } else {
        if(len < x) {
            waiting_for_desired = true;
            desired_x = x;
            x = len;
        }
    }
    redrawyx(contents);
}
void mvu(contents contents, long times) { mvd(contents,-times); }


static bool isDeliminator(char ch) {
    for(unsigned int i = 0; i < DELIMINATORS().length(); i++)
        if(DELIMINATORS()[i] == ch) return true;
    return false;
}
void mvfw(contents contents,unsigned long words) {
}
void mvbw(contents contents,unsigned long words) {
}


void mvf(contents contents, unsigned long times) {
    std::vector<std::string> cont = *contents;
    unsigned long newx = x + times;
    while(cont[y].length() + 1 <= newx) {
        try {
            y++;
            newx -= cont.at(y).length() + 1;
        } catch(...) {
            break;
        }
    }
    if(y >= cont.size()) y = cont.size()-1;
    x = newx;
    show_message((std::string("for (x,y): (") + int_to_str(x)
                  + "," + int_to_str(y) + ")").c_str());
    redrawyx(contents);
}
void mvb(contents contents, unsigned long times) {
    std::vector<std::string> cont = *contents;
    long newx = x - times;
    while(newx < 0) {
        try {
            y--;
            newx += cont.at(y).length();
        } catch(...) {
            break;
        }
    }
    if(y < 0) y = 0;
    if(x < 0) {
        x = 0;
    } else {
        x = newx;
    }
    show_message((std::string("back (x,y): (") + int_to_str(x)
                  + "," + int_to_str(y) + ")").c_str());
    redrawyx(contents);
}
