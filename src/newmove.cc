#include <ncurses.h>

#include "configuration.hh"
#include "int_to_str.hh"
#include "key_listeners.hh"
#include "newmove.hh"
#include "show_message.hh"

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

static void redrawyx() {
    move(y,to_visual((*get_contents())[y],x));
}

void mvrel(unsigned long y,unsigned long x) { mvd(y); mvf(x); }

void mvcol(unsigned long col) {
    unsigned int len = (*get_contents())[y].length();
    if(len >= col) {
        x = col;
        waiting_for_desired = false;
    } else {
        show_message((std::string("Can't move to column: ")
                      + int_to_str(col)).c_str());
    }
    redrawyx();
}

void mvsot() {
    mvsol();
    const std::string& str = (*get_contents())[y];
    for(unsigned int i = 0; i < str.length(); i++)
        if(str[i] == ' ' || str[i] == '\t') mvf();
        else break;
}

void mveol() { mvcol((*get_contents())[y].length()); }
void mvsol() { mvcol(0); }

void mvsop() {
    y = 0;
    x = 0;
    redrawyx();
}
void mveop() {
    y = (*get_contents()).size();
    x = 0;
    redrawyx();
}

void mvd(long times) {
    std::vector<std::string> cont = *get_contents();
    if(y + times < 0 || y + times >= cont.size()) {
        show_message("Can't move to that location (start/end of buffer)");
        return;
    }
    y += times;
    unsigned int len = (*get_contents())[y].length();
    if(waiting_for_desired) {
        if(len < x) {
            x = len;
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
    redrawyx();
}
void mvu(long times) { mvd(-times); }


static bool isDeliminator(char ch) {
    for(unsigned int i = 0; i < DELIMINATORS().length(); i++)
        if(DELIMINATORS()[i] == ch) return true;
    return false;
}
void mvfw(unsigned long words) {
}
void mvbw(unsigned long words) {
}


static inline unsigned long fixLen(unsigned long len) {
    return len == 0 ? 1 : len;
}
void mvf(unsigned long times) {
    std::vector<std::string> cont = *get_contents();
    unsigned long newx = x + times;
    while(true) {
        unsigned long len = fixLen(cont[y].length());
        //if(newx > 
    }
    while(fixLen(cont[y].length()) <= newx && newx > 0) {
        try {
            y++;
            newx -= fixLen(cont.at(y).length());
        } catch(...) {
            break;
        }
    }
    if(y >= cont.size()) y = cont.size()-1;
    x = newx;
    show_message((std::string("for (x,y): (") + int_to_str(x) + "," + int_to_str(y) + ")").c_str());
    redrawyx();
}
void mvb(unsigned long times) {
    std::vector<std::string> cont = *get_contents();
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
    show_message((std::string("back (x,y): (") + int_to_str(x) + "," + int_to_str(y) + ")").c_str());
    redrawyx();
}



// the following are used for function pointers.
void mvd1 () { mvd (); }
void mvu1 () { mvu (); }
void mvf1w() { mvfw(); }
void mvb1w() { mvbw(); }
void mvf1 () { mvf (); }
void mvb1 () { mvb (); }
