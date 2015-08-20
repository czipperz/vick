#ifndef HEADER_GUARD_NEW_MOVE_H
#define HEADER_GUARD_NEW_MOVE_H

void mvrel(unsigned long y,unsigned long x);

void mvcol(unsigned long col);

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
