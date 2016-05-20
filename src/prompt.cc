/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#include <string>

#include "prompt.hh"
#include "configuration.hh"
#include "key_aliases.hh"
#include "contents.hh"
#include "file_contents.hh"
#include "show_message.hh"

namespace vick {

boost::optional<std::string> prompt(const std::string& message) {
    std::string text;
    int b_y, b_x, x, y;
    getyx(stdscr, b_y, b_x);
    getmaxyx(stdscr, y, x);

    --y;
    x = 0;
    move(y, x);
    clrtoeol();
    printw("%s", message.c_str());
    move(y, message.length());

    while (true) {
        char c = getch();
        if (c == QUIT_KEY) {
            move(b_y, b_x);
            return boost::none;
        }
        switch (c) {
            case ERR:
                endwin();
                std::cout << "ERROR character: " << ERR;
                exit(2);
                break;
            case BACKSPACE:
            case CONTROL_H:
                if (text.size())
                    text.erase(text.begin() + --x);
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
                move(y, x++ + message.length());
                addch(c);
                text += c;
                break;
        }
    }
}

boost::optional<bool> prompt_yn(const std::string& message) {
    int b_y, b_x, x, y;
    boost::optional<bool> answer;
    getyx(stdscr, b_y, b_x);
    getmaxyx(stdscr, y, x);

    --y;
    x = 0;

print:
    move(y, 0);
    clrtoeol();
    printw("%s[y,n] ", message.c_str());
    move(y, message.length());

    char ch = getch();
    if (ch == 'y') {
        answer = true;
        goto cleanup;
    }
    if (ch == 'n') {
        answer = false;
        goto cleanup;
    }
    if (ch == QUIT_KEY) {
        answer = boost::none;
        goto cleanup;
    }
    goto print;

cleanup:
    move(b_y, b_x);
    return answer;
}

boost::optional<bool> prompt_yes_no(const std::string& message) {
    boost::optional<std::string> opt;
    while (true) {
        opt = prompt(message + "[yes,no] ");
        if (not opt)
            return boost::none;
        if (*opt == "yes")
            return true;
        if (*opt == "no")
            return false;
    }
}
}
