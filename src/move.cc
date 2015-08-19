#include <ncurses.h>
#include <string.h>

#include "configuration.hh"
#include "int_to_str.hh"
#include "key_listeners.hh"
#include "move.hh"
#include "show_message.hh"

//#define _DEBUG

static int
    y,x,
    vis_y,vis_x,
    desired_x,
    rows,cols;

static bool waiting_for_desired;

static int to_visual(const std::string& cont, int x) {
    int til = 0;
    int xx = x;
    for(std::string::const_iterator i =  cont.begin();
                                    i <= cont.begin() + x; i++) {
        if(*i == '\t') {
            xx += TAB_SIZE() - 1 - til;
            til = 0;
        } else {
            til++;
            til %= TAB_SIZE();
        }
    }
    //show_message(int_to_str(xx).c_str());
    return xx;
}

static int from_visual(const std::string& cont, int x) {
    int til = 0;
    int xx = x;
    for(std::string::const_iterator i =  cont.begin();
                                    i <= cont.begin() + x; i++) {
        if(*i == '\t') {
            xx -= TAB_SIZE() - 1 - til;
            til = 0;
        } else {
            til++;
            til %= TAB_SIZE();
        }
    }
    show_message(int_to_str(xx).c_str());
    return xx;
}

void mv(int _y, int _x) {
    if(_y == y && _x == x) return;
    getmaxyx(stdscr,rows,cols); //row & col assigned to dimensions

    std::vector<std::string>* cont = get_contents();

    if(_y >= 0 && _y < cont->size() && _y < rows - 2) {
        y=_y;
        int len = (*cont)[_y].length();
        if(waiting_for_desired) {
            len--;
            if(len < _x) {
                x = len;
            } else if(len >= desired_x) {
                x = desired_x;
                waiting_for_desired = false;
            } else {
                x = len;
            }
        } else if(_x >= len) {
            waiting_for_desired = true;
            desired_x=x;
            if(len == 0) len++;
            x=len-1;
        } else if(_x >= 0) {
            x=_x;
        } //else -- off left side
    }
    move(y,to_visual((*cont)[y],x));

#ifdef _DEBUG
    show_message((std::string("mv: (_y,_x,desired_x,waiting_for_desired): (")
                  + int_to_str(_y) + ","
                  + int_to_str(_x) + ","
                  + int_to_str(desired_x) + ","
                  + bool_to_str(waiting_for_desired) + ")").c_str());
#endif
}

void mvcol(int col)       { mv(     y,    col); }
void mvrel(int _y,int _x) { mv(y + _y, x + _x); }

void mveol() {
    int len = (*get_contents())[y].length();
    if(len == 0) len++;
    mvcol(len - 1);
}
void mvsol() { mvcol(0);     }

void mvsop() { mv(0,0);      }
void mveop() { mv(rows-1,0); }

static const char deliminators[] = "!@#$%^&*()-_=+[]{};:<>,.'\"/?`~| ";

static bool isDeliminator(char ch) {
    for(int i = 0; i < strlen(deliminators); i++)
        if(deliminators[i] == ch) return true;
    return false;
}

void mvfw() {
    std::vector<std::string>* cont = get_contents();
    //move forward over (possible) sequence of non delmininators
    //move forward over (possible) sequence of deliminators to last
}
void mvbw() {
    std::vector<std::string>* cont = get_contents();
    //move back over (possible) sequence of deliminators
    if(isDeliminator((*cont)[y][x])) {
        mvf();
    }
    //move back over (possible) sequence of non delminators
}

void mvd(int times) {
    int _y = y + 1,
        _x = x;
    if(_y == y && _x == x) return;
    getmaxyx(stdscr,rows,cols); //row & col assigned to dimensions

    std::vector<std::string>* cont = get_contents();

    if(_y >= 0 && _y < cont->size() && _y < rows - 2) {
        y=_y;
        int len = (*cont)[_y].length();
        if(waiting_for_desired) {
            len--;
            if(len < _x) {
                x = len;
            } else if(len >= desired_x) {
                x = desired_x;
                waiting_for_desired = false;
            } else {
                x = len;
            }
        } else if(_x >= len) {
            waiting_for_desired = true;
            desired_x=x;
            if(len == 0) len++;
            x=len-1;
        } else if(_x >= 0) {
            x=_x;
        } //else -- off left side
    }
    //int tabed = remove_tabs(cont,y);
    //if(tabed < 0) tabed = 0;
    move(y,x);

#ifdef _DEBUG
    show_message((std::string("mvd: ("//tabed
                              "y,x): (")
                  //+ int_to_str(tabed) + ","
                  + int_to_str(y) + ","
                  + int_to_str(x) + ")").c_str());
#endif
}
void mvu(int times) { mvrel(-times,      0); }
void mvr(int times) { mvrel(     0,  times); }
void mvl(int times) { mvrel(     0, -times); }
void mvf(int times) { for(int i = 0; i < times; i++) mvf1(); }
void mvb(int times) { for(int i = 0; i < times; i++) mvb1(); }
void mvf1() {
    if((*get_contents())[y].length() == x) {
        mvd();
        mvsol();
    } else {
        mvr();
    }
}
void mvb1() {
    if(x == 0) {
        mvu();
        mveol();
    } else {
        mvl();
    }
}

void mvl1() { mvl(1); }
void mvr1() { mvr(1); }
void mvd1() { mvd(1); }
void mvu1() { mvu(1); }

void mvsot() {
    mvsol();
    const std::string& str = (*get_contents())[y];
    for(int i = 0; i < str.length(); i++)
        if(str[i] == ' ' || str[i] == '\t') mvr();
        else break;
}
