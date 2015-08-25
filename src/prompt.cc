#include <ncurses.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "key_aliases.hh"

std::string prompt_for_test(std::string message, unsigned int y) {
    std::string text;
    int b_y,b_x,
        x = 0,
        xtrack = 0;
    getyx(stdscr,b_y,b_x);

    move(y,x);
    printw("%s",message.c_str());
    x += message.length();
    move(y,x);

    while(true) {
        std::string str;
        char c;
        while(true) {
            switch(getch()) {
            case ERR:
                std::cout << "ERROR character: " << ERR;
                endwin();
                exit(2);
                break;
            case _escape:
                // timeout(0);//if waiting char then get
                // char ch = getch();
                // if(ch == -1) {
                move(b_y,b_x);
                return NULL;
                // }
                // timeout(-1);
                break;
            default:
                move(y, ++xtrack);
                addch(c);
                str += c;
                break;
            }
        }
    }

    return text;
}

std::string prompt_for_test(std::string message) {
    int y,x;
    getmaxyx(stdscr,y,x);
    return prompt_for_test(message,y-1);
}
