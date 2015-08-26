#include <ncurses.h>
#include "class_contents.hh"

contents::contents(std::vector<std::string>* cont)
    : cont(cont),
      y(0),
      x(0),
      desired_x(0),
      y_offset(0),
      waiting_for_desired(false) {
    getmaxyx(stdscr,max_y,max_x);
}
contents::contents(long y, long x)
    : cont(new std::vector<std::string>()),
      y(y),
      x(x),
      desired_x(0),
      y_offset(0),
      waiting_for_desired(false) {
    getmaxyx(stdscr,max_y,max_x);
}
contents::~contents() {
    if(this->cont) delete this->cont;
}


contents::contents(const contents& other)
    : cont(other.cont),
      y(other.y),
      x(other.x),
      desired_x(other.desired_x),
      max_y(other.max_y),
      max_x(other.max_x),
      waiting_for_desired(other.waiting_for_desired) { }
contents& contents::operator=(const contents& other) {
    if(this != &other) {
        delete this->cont;
        *this->cont               = *other.cont;
        this->y                   = other.y;
        this->x                   = other.x;
        this->desired_x           = other.desired_x;
        this->max_y               = other.max_y;
        this->max_x               = other.max_x;
        this->y_offset            = other.y_offset;
        this->waiting_for_desired = other.waiting_for_desired;
    }
    return *this;
}


#if __cplusplus >= 201103L
contents::contents(contents&& other)
    : cont(std::move(other.cont)),
      y(other.y),
      x(other.x),
      desired_x(other.desired_x),
      max_y(other.y),
      max_x(other.x),
      waiting_for_desired(other.waiting_for_desired) {
    other.cont = nullptr;
}
contents& contents::operator=(contents&& other) {
    if(this != &other) {
        delete this->cont;
        this->cont                = other.cont;
        other.cont                = NULL;
        this->y                   = other.y;
        this->x                   = other.x;
        this->desired_x           = other.desired_x;
        this->max_y               = other.max_y;
        this->max_x               = other.max_x;
        this->y_offset            = other.y_offset;
        this->waiting_for_desired = other.waiting_for_desired;
    }
    return *this;
}
#endif


void contents::push_back(const std::string& str) {
    this->cont->push_back(str);
}
