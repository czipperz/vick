#include <ncurses.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "contents.hh"
#include "hooks.hh"
#include "file_contents.hh"
#include "visual.hh"

static contents cont;

void init(std::vector<std::string> vec) {
    cont = contents(vec);
    print_contents(cont);
}

contents& get_contents() { return cont; }

void print_contents(const contents& contents) {
    clear();
    int y = 0;

    int fin_y,fin_x; // if none set then random!

    for(unsigned int i = contents.y_offset;
        i < contents.cont.size()
            && i < contents.max_y - 1 + contents.y_offset; i++) {

        unsigned int x = 0;
        const std::string& line = contents.cont[i];
        int til = 0;

        if(line.begin() == line.end()) {
            if(contents.y == i && contents.x == 0) {
                fin_y = y;
                fin_x = x;
            }
        } else {
            for(std::string::const_iterator it = line.begin(); it < line.end(); it++) {
                if(*it == '\t') {
                    x += TAB_SIZE - til - 1;
                    if(x >= contents.max_x) {
                        x = -1;
                        y++;
                    }
                    move(y,x);
                    til = 0;
                } else {
                    addch(*it);
                    til++;
                    til %= TAB_SIZE;
                }
                if(x == contents.max_x) {
                    til = 0;
                    move(++y, x = 0);
                    addch(*it);
                }
                if(contents.y == i && contents.x == it - line.begin()) {
                    fin_y = y;
                    fin_x = x;
                }
                x++;
                move(y,x);
            }
        }
        move(++y,0);
    }
    //contents.y, to_visual(contents.cont[contents.y],contents.x)
    move(fin_y,fin_x);
    proc_hook(Hook::REFRESH);
}
