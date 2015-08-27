#include <ncurses.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "newmove.hh"
#include "hooks.hh"

static contents* cont;

void init(std::vector<std::string>* vec) {
    cont = new contents(vec);
    print_contents(cont);
}

contents* get_contents() { return cont; }

void print_contents(const contents* contents) {
    clear();
    int b_y,b_x,
        y = 0;
    getyx(stdscr,b_y,b_x);

    for(unsigned int i = contents->y_offset;
        i < contents->cont->size()
            && i < contents->max_y - 1 + contents->y_offset; i++) {
        unsigned int x = 0;
        std::string line = (*contents->cont)[i];
        int til = 0;
        for(unsigned int i = 0; i < line.length(); i++) {
            if(line[i] == '\t') {
                x += TAB_SIZE - til - 1;
                if(x >= contents->max_x) {
                    x = 0;
                    y++;
                }
                move(y,x);
                til = 0;
            } else {
                addch(line[i]);
                til++;
                til %= TAB_SIZE;
            }
            x++;
            if(x-1 == contents->max_x) {
                addch('\\');
                x = 0;
                ++y;
            }
            move(y,x);
        }
        move(++y,0);
    }
    move(contents->y,to_visual((*contents->cont)[contents->y],contents->x));
    proc_hook(Hook::REFRESH);
}
