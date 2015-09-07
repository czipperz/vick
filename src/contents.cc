#include <ncurses.h>
#include "contents.hh"

contents::contents(std::vector<std::string> cont, mode* m)
    : m(m)
    , cont(cont) {
    refreshmaxyx();
}
contents::contents(mode* m)
    : m(m)
    , cont(std::vector<std::string>()) {
    refreshmaxyx();
}
contents::contents(long y, long x, mode* m)
    : m(m)
    , cont(std::vector<std::string>())
    , y(y)
    , x(x) {
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
