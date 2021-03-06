/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <ncurses.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "basic_commands.hh"
#include "command_listeners.hh"
#include "configuration.hh"
#include "file_contents.hh"
#include "key_aliases.hh"
#include "show_message.hh"

namespace vick {

std::shared_ptr<change>
quit_command(contents&, boost::optional<int>) {
    endwin();
    exit(0);
}

struct replace_c : public change {
    move_t y, x;
    char n, o;
    replace_c(move_t y, move_t x, char n, char o)
        : y(y)
        , x(x)
        , n(n)
        , o(o) {}
    virtual bool is_overriding() const noexcept override {
        return true;
    }
    virtual void undo(contents& contents) override {
        contents.y = y;
        contents.x = x;
        contents.cont[contents.y][contents.x] = o;
    }
    virtual void redo(contents& contents) override {
        contents.y = y;
        contents.x = x;
        contents.cont[contents.y][contents.x] = n;
    }
    virtual std::shared_ptr<change>
    regenerate(const contents& contents) const override {
        return std::make_shared<replace_c>(contents.y, contents.x, n,
                                           contents.cont[contents.y]
                                                        [contents.x]);
    }
};

std::shared_ptr<change>
replace_character(contents& contents, boost::optional<int>) {
    std::shared_ptr<change> ret =
        std::make_shared<replace_c>(contents.y, contents.x, getch(),
                                    contents.cont[contents.y]
                                                 [contents.x]);
    ret->redo(contents);
    return ret;
}

struct remove_c : public change {
    move_t y, x;
    char o;
    remove_c(move_t y, move_t x, char o)
        : y(y)
        , x(x)
        , o(o) {}
    virtual bool is_overriding() const noexcept override {
        return true;
    }
    virtual void undo(contents& contents) override {
        contents.y = y;
        contents.x = x;
        contents.cont[contents.y].insert(contents.x, 1, o);
    }
    virtual void redo(contents& contents) override {
        contents.y = y;
        contents.x = x;
        contents.cont[contents.y].erase(contents.x, 1);
    }
    virtual std::shared_ptr<change>
    regenerate(const contents& contents) const override {
        return std::make_shared<remove_c>(contents.y, contents.x,
                                          contents.cont[contents.y]
                                                       [contents.x]);
    }
};

std::shared_ptr<change>
remove_character(contents& contents, boost::optional<int>) {
    std::shared_ptr<change> ret =
        std::make_shared<remove_c>(contents.y, contents.x,
                                   contents.cont[contents.y]
                                                [contents.x]);
    ret->redo(contents);
    return ret;
}

std::shared_ptr<change>
color_test_command(contents&, boost::optional<int>) {
    show_message(
        "has_colors(): ``" + std::to_string(has_colors()) +
        "``, can_change_color(): ``" +
        std::to_string(can_change_color()) + "``, init_color(): ``" +
        std::to_string(init_color(COLOR_RED, 700, 0, 0)) + "``");
    return nullptr;
}
}
