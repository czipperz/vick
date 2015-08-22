#include <ncurses.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "file_contents.hh"
#include "newmove.hh"

contents::contents(std::vector<std::string>* cont)
    : cont(cont),
      y(0),
      x(0),
      desired_x(0),
      waiting_for_desired(false) { }

contents::contents(long y, long x)
    : cont(new std::vector<std::string>()),
      y(y),
      x(x),
      desired_x(0),
      waiting_for_desired(false) { }

contents::~contents() { delete this->cont; }

void contents::push_back(const std::string& str) {
    this->cont->push_back(str);
}

long contents::get_y() const { return this->y; }
long contents::get_x() const { return this->x; }
long contents::get_desired_x() const { return this->desired_x; }
bool contents::get_waiting_for_desired() const { return this->waiting_for_desired; }

static contents* cont;

void init(std::vector<std::string>* vec) {
    cont = new contents(vec);
    print_contents(cont,0);
}

contents& get_contents() { return *cont; }

void print_contents(contents* contents, int y_offset) {
    int b_y,b_x,
        rows,cols,
        y = 0;
    getyx(stdscr,b_y,b_x);
    getmaxyx(stdscr,rows,cols);

    for(unsigned int i = y_offset; i < contents->cont->size(); i++) {
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
