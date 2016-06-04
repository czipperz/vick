/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <ncurses.h>
#include <locale>
#include <string>
#include <vector>

#include "configuration.hh"
#include "contents.hh"
#include "file_contents.hh"
#include "file_contents.hh"
#include "hooks.hh"
#include "open_file.hh"
#include "print_contents.hh"
#include "show_message.hh"
#include "visual.hh"

namespace vick {

static contents cont;

void init(int argc, char** argv) {
    if (argc) {
        open_file(cont, *argv);
    } else {
        cont.push_back("");
    }
    get_contents().refreshmaxyx();
    print_contents(cont);
}

contents& get_contents() { return cont; }

void get_window_dimensions(const contents& contents, move_t& firsty,
                           move_t& lasty, move_t& lastx) {
    const std::locale locale;
    move_t x;
    move_t y = 0;

    firsty = std::min(contents.y_offset, contents.y);

    auto line = std::begin(contents.cont) + firsty;

    const auto endline = std::end(contents.cont);
    for (; line != endline; ++line) {
        lastx = 0;
        x = 0;

        for (auto ch = std::begin(*line), end = std::end(*line);
             ch != end; ++ch) {

            lastx++;
            // moves forward based on character at point
            x += char_size(*ch, x, locale);
            if (x > contents.max_x) {
                x -= contents.max_x;
#define yOutOfBounds                                                 \
    do {                                                             \
        if (++y > contents.max_y - 1 - BOTTOM_HEIGHT) {              \
            goto end;                                                \
        }                                                            \
    } while (0)
                yOutOfBounds;
            }
        }

        // at end so that lastx is set correctly for the line
        yOutOfBounds;
#undef yOutOfBounds
    }
    y--;
end:
    // if (lastx != 0) lastx--;
    lasty = line - std::begin(contents.cont);

    if (contents.y > lasty) {
        firsty += contents.y - lasty;
        // goto top;
    }
}

void print_contents(contents& contents) {
    clear();
    move_t y = 0, fin_y = 0, fin_x = 0;
    move_t lasty, lastx;

    get_window_dimensions(contents, contents.y_offset, lasty, lastx);

    for (auto i = contents.y_offset;
         i < contents.cont.size() and
         i < contents.max_y - 1 + contents.y_offset;
         i++) {

        move_t x = 0;
        const std::string& line = contents.cont[i];

        if (line.empty()) {
            if (contents.y == i and contents.x == 0) {
                fin_y = y;
                fin_x = x;
            }
        } else {
            for (auto it = line.begin(); it < line.end(); it++) {
                x += char_size(*it, x, std::locale());
                addch(*it);
                if (x >= contents.max_x) {
                    x = 0;
                    y++;
                }
                move(y, x);
                if (contents.y == i and
                    contents.x ==
                        static_cast<move_t>(it - line.begin())) {
                    fin_y = y;
                    fin_x = x - 1;
                }
            }
            if (contents.y == i and contents.x >= line.size()) {
                fin_y = y;
                fin_x = x - (contents.is_inserting ? 0 : 1);
            }
        }
        move(++y, 0);
    }
    // contents.y, to_visual(contents.cont[contents.y],contents.x)
    move(fin_y, fin_x);
    hooks::refresh.proc(contents);
    show_message(
        std::string("firsty: ") + std::to_string(contents.y_offset) +
        " lasty: " + std::to_string(lasty) + " lastx: " +
        std::to_string(lastx) + " (" + std::to_string(contents.y) +
        ", " + std::to_string(contents.x) + "), max_x: " +
        std::to_string(contents.max_x) + " changes_i: " +
        std::to_string(contents.changes_i));

    refresh();
}
}
