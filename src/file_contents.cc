#include <ncurses.h>
#include <string>
#include <vector>

#include "open_file.hh"
#include "file_contents.hh"
#include "configuration.hh"
#include "contents.hh"
#include "hooks.hh"
#include "file_contents.hh"
#include "visual.hh"
#include "show_message.hh"

namespace vick {

static contents cont;

void init(int argc, char** argv)
{
    if (argc) {
        open_file(cont, *argv);
    } else {
        cont.push_back("");
    }
    print_contents(cont);
}

contents& get_contents()
{
    return cont;
}

void print_contents(contents& contents)
{
    if (contents.y >= contents.y_offset + contents.max_y - 2) {
        contents.y_offset = contents.y - contents.max_y + 2;
    }
    if (contents.y < contents.y_offset) {
        contents.y_offset = contents.y;
    }

    clear();
    move_t y = 0, fin_y, fin_x; // if none set then random!

    for (auto i = contents.y_offset;
         i < contents.cont.size() and i < contents.max_y - 1 + contents.y_offset;
         i++) {

        move_t x = 0;
        const std::string& line = contents.cont[i];

        if (line.empty()) {
            if (contents.y == i and contents.x == 0) {
                fin_y = y;
                fin_x = x;
            }
        } else {
            int til = 0;
            for (auto it = line.begin(); it < line.end(); it++) {
                if (*it == '\t') {
                    x += TAB_SIZE - til - 1;
                    if (x >= contents.max_x) {
                        x = -1;
                        y++;
                    }
                    move(y, x);
                    til = 0;
                } else {
                    addch(*it);
                    til++;
                    til %= TAB_SIZE;
                }
                if (x == contents.max_x) {
                    til = 0;
                    move(++y, x = 0);
                    addch(*it);
                }
                if (contents.y == i and contents.x == static_cast<move_t>(it - line.begin())) {
                    fin_y = y;
                    fin_x = x;
                }
                x++;
                move(y, x);
            }
            if (contents.y == i and contents.x >= line.size()) {
                fin_y = y;
                fin_x = x + (contents.is_inserting ? 0 : -1);
            }
        }
        move(++y, 0);
    }
    // contents.y, to_visual(contents.cont[contents.y],contents.x)
    move(fin_y, fin_x);
    hook::proc(hook::refresh, contents);

    refresh();
}

}
