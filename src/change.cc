/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "change.hh"
#include <algorithm>
#include "contents.hh"

namespace vick {
std::shared_ptr<change> change::regenerate_and_apply(contents& cont) {
    auto x = regenerate(cont);
    x->redo(cont);
    return x;
}

combination_change::combination_change(std::initializer_list<std::shared_ptr<change> > list)
    : changes(std::move(list)) {
}

void combination_change::add_change(std::shared_ptr<change> c) {
    changes.push_back(std::move(c));
}

bool combination_change::is_overriding() const noexcept {
    return std::any_of(changes.begin(), changes.end(),
                       [](const std::shared_ptr<change>& ptr) {
                           return ptr->is_overriding();
                       });
}

void combination_change::undo(contents& c) {
    std::for_each(changes.begin(), changes.end(),
                  [&c](std::shared_ptr<change>& ptr) {
                      ptr->undo(c);
                  });
}

void combination_change::redo(contents& c) {
    std::for_each(changes.begin(), changes.end(),
                  [&c](std::shared_ptr<change>& ptr) {
                      ptr->redo(c);
                  });
}

std::shared_ptr<change>
combination_change::regenerate(const contents& c) const {
    std::shared_ptr<combination_change> change =
        std::make_shared<combination_change>();
    change->changes.reserve(changes.size());
    std::for_each(changes.begin(), changes.end(),
                  [&c, &change](
                      const std::shared_ptr<vick::change>& ptr) {
                      change->changes.push_back(ptr->regenerate(c));
                  });
    return change;
}

combination_change::combination_change(const combination_change& other)
    : changes(other.changes) {}
combination_change::combination_change(combination_change&& other)
    : changes(std::move(other.changes)) {}
combination_change& combination_change::operator=(const combination_change& other) {
    changes = other.changes;
    return *this;
}
combination_change& combination_change::operator=(combination_change&& other) {
    changes = std::move(other.changes);
    return *this;
}

insertion_change::insertion_change(std::size_t y, std::size_t x,
                                   const std::string& str)
    : y(y)
    , x(x)
    , str(str) {}
insertion_change::insertion_change(std::size_t y, std::size_t x, std::string&& str)
    : y(y)
    , x(x)
    , str(std::move(str)) {}

bool insertion_change::is_overriding() const noexcept { return true; }

void insertion_change::undo(contents& c) {
    assert(y < c.cont.size());
    assert(x < c.cont[y].size());
    assert(x + str.size() < c.cont[y].size());
    c.cont[y].erase(x, str.size());
}

void insertion_change::redo(contents& c) {
    assert(y <= c.cont.size());
    if (y == c.cont.size()) {
        c.cont.push_back(str);
    } else {
        assert(x <= c.cont[y].size());
        c.cont[y].insert(x, str);
    }
}

std::shared_ptr<change>
insertion_change::regenerate(const contents& c) const {
    return std::make_shared<insertion_change>(c.y, c.x, str);
}

insertion_change::insertion_change(const insertion_change& other)
    : y(other.y)
    , x(other.x)
    , str(other.str) {}
insertion_change::insertion_change(insertion_change&& other)
    : y(other.y)
    , x(other.x)
    , str(std::move(other.str)) {}
insertion_change& insertion_change::
operator=(const insertion_change& other) {
    y = other.y;
    x = other.x;
    str = other.str;
    return *this;
}
insertion_change& insertion_change::
operator=(insertion_change&& other) {
    y = other.y;
    x = other.x;
    str = std::move(other.str);
    return *this;
}

removal_change::removal_change(std::size_t y, std::size_t x,
                               const std::string& str)
    : insertion_change(y, x, str) {}
removal_change::removal_change(std::size_t y, std::size_t x,
                               std::string&& str)
    : insertion_change(y, x, std::move(str)) {}

bool removal_change::is_overriding() const noexcept {
    return true;
}

void removal_change::undo(contents& c) {
    insertion_change::redo(c);
}

void removal_change::redo(contents& c) {
    insertion_change::undo(c);
}

std::shared_ptr<change>
removal_change::regenerate(const contents& c) const {
    return std::make_shared<removal_change>(c.y, c.x, str);
}
}
