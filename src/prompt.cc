#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <string>

#include "key_aliases.hh"
#include "contents.hh"
#include "file_contents.hh"
#include "show_message.hh"

std::string prompt(const std::string& message)
{
    std::string text;
    int b_y, b_x, x, y, xtrack = 0;
    getyx(stdscr, b_y, b_x);
    getmaxyx(stdscr, y, x);

    --y; x = 0;
    move(y, x);
    printw("%s", message.c_str());
    x += message.length();
    move(y, x);

    while (true) {
        char c = getch();
        switch (c) {
            case ERR:
                std::cout << "ERROR character: " << ERR;
                endwin();
                exit(2);
                break;
            case _escape:
                move(b_y, b_x);
                return "";
            case _backspace:
            case _control_h:
                if (text.size()) text.erase(text.begin() + --xtrack);
                move(y, 0);
                clrtoeol();
                for (size_t i = 0; i < message.size(); i++) {
                    move(y, i);
                    addch(message[i]);
                }
                for (size_t i = 0; i < text.size(); i++) {
                    move(y, i + message.size());
                    addch(text[i]);
                }
                break;
            case '\n':
                move(b_y, b_x);
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
