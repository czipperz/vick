#include <ncurses.h>
#include "contents.hh"

contents::contents(std::vector<std::string> cont, mode* m) : m(m), cont(cont)
{
    refreshmaxyx();
}
contents::contents(mode* m) : m(m), cont(std::vector<std::string>())
{
    refreshmaxyx();
}
contents::contents(move_t y, unsigned long x, mode* m)
    : m(m), cont(std::vector<std::string>()), y(y), x(x)
{
    refreshmaxyx();
}

bool contents::operator()(char ch) const
{
    return (*this->m)(ch);
}

contents::~contents()
{
    if (delete_mode) delete m;
}
contents::contents(const contents& other)
    : m(new mode(*other.m)), cont(other.cont), changes(other.changes),
      y(other.y), x(other.x), desired_x(other.desired_x),
      y_offset(other.y_offset), max_y(other.max_y), max_x(other.max_x),
      waiting_for_desired(other.waiting_for_desired), refresh(other.refresh),
      delete_mode(other.delete_mode)
{
}
contents::contents(contents&& other)
    : m(other.m), cont(other.cont), changes(other.changes), y(other.y),
      x(other.x), desired_x(other.desired_x), y_offset(other.y_offset),
      max_y(other.max_y), max_x(other.max_x),
      waiting_for_desired(other.waiting_for_desired), refresh(other.refresh),
      delete_mode(other.delete_mode)
{
}
contents& contents::operator=(const contents& other)
{
    if (this == &other) return *this;
    if (delete_mode && m) delete m;
    m = new mode(*other.m);
    cont = other.cont;
    y = other.y;
    x = other.x;
    desired_x = other.desired_x;
    y_offset = other.y_offset;
    max_y = other.max_y;
    max_x = other.max_x;
    waiting_for_desired = other.waiting_for_desired;
    refresh = other.refresh;
    delete_mode = other.delete_mode;
    _changes = other._changes;
    return *this;
}
contents& contents::operator=(contents&& other)
{
    if (this == &other) return *this;
    if (delete_mode && m) delete m;
    m = other.m;
    cont = other.cont;
    y = other.y;
    x = other.x;
    desired_x = other.desired_x;
    y_offset = other.y_offset;
    max_y = other.max_y;
    max_x = other.max_x;
    waiting_for_desired = other.waiting_for_desired;
    refresh = other.refresh;
    delete_mode = other.delete_mode;
    _changes = other._changes;
    return *this;
}

void contents::refreshmaxyx()
{
    getmaxyx(stdscr, max_y, max_x);
}

void contents::push_back(const std::string& str)
{
    this->cont.push_back(str);
}
