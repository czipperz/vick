#include "newmove.hh"
#include "key_listeners.hh"
#include "move.hh"

void mvrel(long y, long x) { mvrel(get_contents(),y,x); }

void mvcol(long col) { mvcol(get_contents(),col); }

void mvsot() { mvsot(get_contents()); }

void mveol() { mveol(get_contents()); }
void mvsol() { mvsol(get_contents()); }

void mvsop() { mvsop(get_contents()); }
void mveop() { mveop(get_contents()); }

void mvd(long times) { mvd(get_contents(),times); }
void mvu(long times) { mvu(get_contents(),times); }

void mvfw(unsigned long words) { mvfw(get_contents(),words); }
void mvbw(unsigned long words) { mvbw(get_contents(),words); }

void mvf(unsigned long times) { mvf(get_contents(),times); }
void mvb(unsigned long times) { mvb(get_contents(),times); }



// the following are used for function pointers.
void mvd1 () { mvd (); }
void mvu1 () { mvu (); }
void mvf1w() { mvfw(); }
void mvb1w() { mvbw(); }
void mvf1 () { mvf (); }
void mvb1 () { mvb (); }
