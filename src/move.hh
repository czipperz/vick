#ifndef HEADER_GUARD_MOVE_H
#define HEADER_GUARD_MOVE_H

void mv   (int  y,int  x);
void mvcol(int col);
void mvrel(int _y,int _x);

void mveol(); //end of line
void mvsol(); //start of line

void mvsot(); //start of text

void mvsop(); //start of page
void mveop(); //end of page

void mvfw (); //forward word
void mvbw (); //backward word

void mvl(int times = 1);
void mvr(int times = 1);
void mvu(int times = 1);
void mvd(int times = 1);
void mvf(int times = 1);
void mvb(int times = 1);

/* {{{ call the above (used for function pointers).  
 * Don't call these. */
void mvl1();
void mvr1();
void mvu1();
void mvd1();
void mvf1();
void mvb1();
/* }}} */

#endif
