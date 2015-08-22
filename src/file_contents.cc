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

contents::contents(const contents& other)
    : cont(other.cont),
      y(other.y),
      x(other.x),
      desired_x(other.desired_x),
      waiting_for_desired(other.waiting_for_desired) { }

contents& contents::operator=(const contents& other) {
    if(this != &other) {
        delete this->cont;
        this->cont                = other.cont;
        this->y                   = other.y;
        this->x                   = other.x;
        this->desired_x           = other.desired_x;
        this->y_offset            = other.y_offset;
        this->waiting_for_desired =
            other.waiting_for_desired;
    }
    return *this;
}

contents::~contents() {
    if(this->cont) delete this->cont;
}

void contents::push_back(const std::string& str) {
    this->cont->push_back(str);
}

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
