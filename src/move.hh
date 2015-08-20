#ifndef HEADER_GUARD_MOVE_H
#define HEADER_GUARD_MOVE_H

/* call "newmove.hh"'s functions with ``get_contents()'' */

void mvrel(long y, long x);

void mvcol(long col);

void mvsot();

void mveol();
void mvsol();

void mvsop();
void mveop();

void mvd(long times = 1);
void mvu(long times = 1);

void mvfw(unsigned long words = 1);
void mvbw(unsigned long words = 1);

void mvf(unsigned long times = 1);
void mvb(unsigned long times = 1);



// the following are used for function pointers.
void mvd1();
void mvu1();
void mvf1w();
void mvb1w();
void mvf1();
void mvb1();

#endif
