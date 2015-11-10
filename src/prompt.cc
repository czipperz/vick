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

boost::optional<std::string> prompt(const std::string& message)
{
    std::string text;
    int b_y, b_x, x, y;
    getyx(stdscr, b_y, b_x);
    getmaxyx(stdscr, y, x);

    --y; x = 0;
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
            case _backspace:
            case _control_h:
                if (text.size()) text.erase(text.begin() + --x);
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

bool prompt_yn(const std::string& message)
{
    int b_y, b_x, x, y;
    bool answer;
    getyx(stdscr, b_y, b_x);
    getmaxyx(stdscr, y, x);

    --y; x = 0;

print:
    move(y, 0);
    clrtoeol();
    printw("%s[y,n] ", message.c_str());
    move(y, message.length());

    switch(getch()) {
        case 'y':
            answer = true;
            goto cleanup;
        case 'n':
            answer = false;
            goto cleanup;
        default:
            goto print;
    }

cleanup:
    move(b_y, b_x);
    return answer;
}

bool prompt_yes_no(const std::string& message)
{
    boost::optional<std::string> opt = boost::none;
    while(!opt || !(*opt == "yes" || *opt == "no")) {
        opt = prompt(message + "[yes,no] ");
    }
    return *opt == "yes";
}
