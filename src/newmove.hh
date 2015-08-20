#ifndef HEADER_GUARD_NEW_MOVE_H
#define HEADER_GUARD_NEW_MOVE_H

#include <string>
#include <vector>

typedef std::vector<std::string>* contents;

void mvline (contents, unsigned long);
void mv     (contents, unsigned long y, unsigned long x);

void mvrel  (contents, long y,          long x);

void mvcol  (contents, unsigned long col);

void mvsot  (contents);

void mveol  (contents);
void mvsol  (contents);

void mvsop  (contents);
void mveop  (contents);

void mvd    (contents, long times = 1);
void mvu    (contents, long times = 1);

void mvfw   (contents, unsigned long words = 1);
void mvbw   (contents, unsigned long words = 1);

void mvf    (contents, unsigned long times = 1);
void mvb    (contents, unsigned long times = 1);

#endif
