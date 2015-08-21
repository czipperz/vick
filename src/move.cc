#include <ncurses.h>
#include "newmove.hh"
#include "move.hh"
#include "file_contents.hh"
#include "show_message.hh"
#include "int_to_str.hh"

static void show() {
    int vy,vx;
    getyx(stdscr,vy,vx);
    show_message((std::string("x,y,vx,vy: ")
                  + int_to_str(get_contents().get_x()) + ","
                  + int_to_str(get_contents().get_y()) + ","
                  + int_to_str(vx) + ","
                  + int_to_str(vy)).c_str());
}

void mvrel(long y, long x) {
    mvrel(get_contents(),y,x);
    show();
}

void mvcol(long col) {
    mvcol(get_contents(),col);
    show();
}

void mvsot() {
    mvsot(get_contents());
    show();
}

void mveol() {
    mveol(get_contents());
    show();
}
void mvsol() {
    mvsol(get_contents());
    show();
}

void mvsop() {
    mvsop(get_contents());
    show();
}
void mveop() {
    mveop(get_contents());
    show();
}

void mvd(long times) {
    mvd(get_contents(),times);
    show();
}
void mvu(long times) {
    mvu(get_contents(),times);
    show();
}

void mvfw(unsigned long words) {
    mvfw(get_contents(),words);
    show();
}
void mvbw(unsigned long words) {
    mvbw(get_contents(),words);
    show();
}

void mvf(unsigned long times) {
    mvf(get_contents(),times);
    show();
}
void mvb(unsigned long times) {
    mvb(get_contents(),times);
    show();
}



// the following are used for function pointers.
void mvd1 () { mvd (); }
void mvu1 () { mvu (); }
void mvf1w() { mvfw(); }
void mvb1w() { mvbw(); }
void mvf1 () { mvf (); }
void mvb1 () { mvb (); }
