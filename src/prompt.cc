#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <string>

#include "key_aliases.hh"

std::string prompt(const std::string& message) {
    std::string text;
    int b_y, b_x, x, y, xtrack = 0;
    getyx(stdscr,b_y,b_x);
    getmaxyx(stdscr,y,x); x = 0; y--;

    move(y,x);
    printw("%s",message.c_str());
    x += message.length();
    move(y,x);

    while(true) {
        char c = getch();
        switch(c) {
        case ERR:
            std::cout << "ERROR character: " << ERR;
            endwin();
            exit(2);
            break;
        case _escape:
            move(b_y,b_x);
            return "";
        case '\n':
            move(b_y,b_x);
            return text;
        default:
            move(y, ++xtrack);
            addch(c);
            text += c;
            break;
        }
    }

    return text;
}
