#include <ncurses.h>
#include <string>
#include <vector>
#include "move.h"
#include "configuration.h"

void print_init_contents(std::vector<std::string>* contents) {
    int b_y,b_x,
        rows,cols,
        y = 0;
    getyx(stdscr,b_y,b_x);
    getmaxyx(stdscr,rows,cols);

    for(unsigned int i = 0; i < contents->size(); i++) {
        int x = 0;
        std::string line = (*contents)[i];
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
