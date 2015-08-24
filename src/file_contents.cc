#include <ncurses.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "newmove.hh"

static contents* cont;

void init(std::vector<std::string>* vec) {
    cont = new contents(vec);
    print_contents(cont);
}

contents& get_contents() { return *cont; }

void print_contents(const contents* contents) {
    int b_y,b_x,
        rows,cols,
        y = 0;
    getyx(stdscr,b_y,b_x);
    getmaxyx(stdscr,rows,cols);

    for(unsigned int i = contents->y_offset; i < contents->cont->size(); i++) {
        int x = 0;
        std::string line = (*contents->cont)[i];
        int til = 0;
        for(int i = 0; i < line.length(); i++) {
            if(line[i] == '\t') {
                for(int j = 1; j < TAB_SIZE() - til; j++) {
                    addch(' ');
                    move(y,++x);
                }
                til = 0;
            } else {
                addch(line[i]);
                til++;
                til %= TAB_SIZE();
            }
            x++;
            if(x-1 == cols) {
                addch('\\');
                x = 0;
                ++y;
            }
            move(y,x);
        }
        move(++y,0);
    }
    move(0,0);
}
