#include <ncurses.h>

#include "file_contents.hh"
#include "hooks.hh"
#include "int_to_str.hh"
#include "move.hh"
#include "newmove.hh"
#include "show_message.hh"

#define _DEBUG

static void show() {
#ifdef _DEBUG
    int vy,vx;
    getyx(stdscr,vy,vx);
    const contents* contents = get_contents();
    show_message((std::string("x,y,vx,vy,desired_x,waiting?: ")
                  + int_to_str (contents->x) + ","
                  + int_to_str (contents->y) + ","
                  + int_to_str (vx) + ","
                  + int_to_str (vy) + ","
                  + int_to_str (contents->desired_x) + ","
                  + bool_to_str(contents->waiting_for_desired)).c_str());
#endif
    print_contents(contents);
    proc_hook(Hook::MOVE);
}

void mvrel(long y, long x) {
    mvrel(*get_contents(),y,x);
    show();
}

void mvcol(long col) {
    mvcol(*get_contents(),col);
    show();
}

void mvsot() {
    mvsot(*get_contents());
    show();
}

void mveol() {
    mveol(*get_contents());
    show();
}
void mvsol() {
    mvsol(*get_contents());
    show();
}

void mvsop() {
    mvsop(*get_contents());
    show();
}
void mveop() {
    mveop(*get_contents());
    show();
}

void mvd(long times) {
    mvd(*get_contents(),times);
    show();
}
void mvu(long times) {
    mvu(*get_contents(),times);
    show();
}

void mvfw(unsigned long words) {
    mvfw(*get_contents(),words);
    show();
}
void mvbw(unsigned long words) {
    mvbw(*get_contents(),words);
    show();
}

void mvf(unsigned long times) {
    mvf(*get_contents(),times);
    show();
}
void mvb(unsigned long times) {
    mvb(*get_contents(),times);
    show();
}



// the following are used for function pointers.
void mvd1 () { mvd (); }
void mvu1 () { mvu (); }
void mvf1w() { mvfw(); }
void mvb1w() { mvbw(); }
void mvf1 () { mvf (); }
void mvb1 () { mvb (); }
