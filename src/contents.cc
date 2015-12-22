#include <ncurses.h>
#include "contents.hh"
#include "hooks.hh"

namespace vick {

contents::contents(std::vector<std::string> cont, mode* buffer_mode) : buffer_mode(buffer_mode), cont(cont)
{
    refreshmaxyx();
    hook::proc(hook::contents_created, *this);
}

contents::contents(mode* buffer_mode) : buffer_mode(buffer_mode), cont(std::vector<std::string>())
{
    refreshmaxyx();
    hook::proc(hook::contents_created, *this);
}

contents::contents(move_t y, move_t x, mode* buffer_mode)
    : buffer_mode(buffer_mode), cont(std::vector<std::string>()), y(y), x(x)
{
    refreshmaxyx();
    hook::proc(hook::contents_created, *this);
}

bool contents::operator()(char ch)
{
    return (*buffer_mode)(*this, ch);
}

contents::~contents()
{
    hook::proc(hook::contents_deleted, *this);
    if (delete_mode) delete buffer_mode;
}

contents::contents(const contents& other)
    : buffer_mode(new mode(*other.buffer_mode)), cont(other.cont), changes(other.changes),
      y(other.y), x(other.x), desired_x(other.desired_x),
      y_offset(other.y_offset), max_y(other.max_y), max_x(other.max_x),
      waiting_for_desired(other.waiting_for_desired), refresh(other.refresh),
      delete_mode(other.delete_mode)
{
}

contents& contents::operator=(const contents& other)
{
    if (this == &other) return *this;
    if (delete_mode) delete buffer_mode;
    buffer_mode = new mode(*other.buffer_mode);
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
    changes = other.changes;
    return *this;
}

contents& contents::operator=(contents&& other)
{
    if (this == &other) return *this;
    if (delete_mode) delete buffer_mode;
    buffer_mode = other.buffer_mode;
    cont = std::move(other.cont);
    y = other.y;
    x = other.x;
    desired_x = other.desired_x;
    y_offset = other.y_offset;
    max_y = other.max_y;
    max_x = other.max_x;
    waiting_for_desired = other.waiting_for_desired;
    refresh = other.refresh;
    delete_mode = other.delete_mode;
    changes = std::move(other.changes);
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

}
