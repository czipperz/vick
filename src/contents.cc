#include <ncurses.h>
#include "contents.hh"

contents::contents(std::vector<std::string> cont, mode* m)
    : cont(cont)
    , y(0)
    , x(0)
    , desired_x(0)
    , y_offset(0)
    , waiting_for_desired(false)
    , m(m) {
    refreshmaxyx();
}
contents::contents(mode* m)
    : cont(std::vector<std::string>())
    , y(0)
    , x(0)
    , desired_x(0)
    , y_offset(0)
    , waiting_for_desired(false)
    , m(m) {
    refreshmaxyx();
}
contents::contents(long y, long x, mode* m)
    : cont(std::vector<std::string>())
    , y(y)
    , x(x)
    , desired_x(0)
    , y_offset(0)
    , waiting_for_desired(false)
    , m(m) {
    refreshmaxyx();
}

bool contents::operator()(char ch) const {
    return (*this->m)(ch);
}

void contents::refreshmaxyx() {
    getmaxyx(stdscr,max_y,max_x);
}

void contents::push_back(const std::string& str) {
    this->cont.push_back(str);
}
