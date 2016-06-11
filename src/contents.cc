/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "contents.hh"
#include <ncurses.h>
#include "hooks.hh"

namespace vick {

contents::contents() {
    refreshmaxyx();
    hooks::contents_created.proc(*this);
}

contents::contents(std::vector<std::string> contents)
    : cont(std::move(contents)) {
    refreshmaxyx();
    hooks::contents_created.proc(*this);
}

bool contents::operator()(char ch) {
    return (*buffer_mode)(*this, ch);
}

contents::~contents() {
    hooks::contents_deleted.proc(*this);
    if (delete_mode)
        delete buffer_mode;
}

contents::contents(const contents& other)
    : buffer_mode(new mode(*other.buffer_mode))
    , cont(other.cont)
    , changes(other.changes)
    , y(other.y)
    , x(other.x)
    , desired_x(other.desired_x)
    , y_offset(other.y_offset)
    , max_y(other.max_y)
    , max_x(other.max_x)
    , waiting_for_desired(other.waiting_for_desired)
    , refresh(other.refresh)
    , delete_mode(other.delete_mode) {}

contents& contents::operator=(const contents& other) {
    if (this == &other)
        return *this;
    if (delete_mode)
        delete buffer_mode;
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

contents& contents::operator=(contents&& other) {
    if (this == &other)
        return *this;
    if (delete_mode)
        delete buffer_mode;
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

void contents::refreshmaxyx() { getmaxyx(stdscr, max_y, max_x); }

void contents::push_back(std::string str) {
    this->cont.push_back(std::move(str));
}
}
