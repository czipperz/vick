#include <vector>
#include <string>
#include <stdlib.h>
#include <ncurses.h>
#include <iostream>

#include "key_aliases.hh"
#include "command_listeners.hh"
#include "file_contents.hh"
#include "show_message.hh"

boost::optional< std::shared_ptr<change> >
    quit_command(contents&, boost::optional<int>) {
    endwin();
    exit(0);
}

static bool key_test_handle(char);

static contents key_test(new mode("Key Test", key_test_handle));

static bool key_test_handle(char other) {
    move(key_test.y, key_test.x);
    if(other == _resize) return true;
    if(other == ':') {
        clear_message();
        command_executor(key_test, boost::none);
        return true;
    }
    printw("'%c':%d", other, other);

    key_test.x += 10;
    if(key_test.x >= get_contents().max_x) {
        key_test.x = 0;
        key_test.y++;
    }
    if(key_test.y >= get_contents().max_y) {
        key_test.y = 1;
    }
    return true;
}

boost::optional< std::shared_ptr<change> > key_test_command(contents& cont, boost::optional<int>) {
    key_test.delete_mode = true;
    key_test.refresh = false;
    key_test.y = 1;
    key_test.x = 1;
    move(0,0);
    printw("[Key test: type anything]");
    cont = key_test;
    return boost::none;
}

struct replace_c : public change {
    unsigned long y,x;
    char n,o;
    replace_c(unsigned long y, unsigned long x, char n, char o) : y(y), x(x), n(n), o(o) {}
    virtual bool is_overriding() override { return true; }
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
    virtual std::shared_ptr<change> regenerate(const contents& contents) const override {
        return std::make_shared<replace_c>(contents.y, contents.x, n, contents.cont[contents.y][contents.x]);
    }
};

boost::optional< std::shared_ptr<change> > replace_character(contents& contents, boost::optional<int>) {
    std::shared_ptr<change> ret = std::make_shared<replace_c>
        (contents.y, contents.x, getch(), contents.cont[contents.y][contents.x]);
    ret->redo(contents);
    return ret;
}
