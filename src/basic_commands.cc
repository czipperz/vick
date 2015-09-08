#include <vector>
#include <string>
#include <stdlib.h>
#include <ncurses.h>
#include <iostream>

#include "command_listeners.hh"
#include "contents.hh"
#include "file_contents.hh"
#include "show_message.hh"

void quit_command(contents&, boost::optional<int>) {
    endwin();
    exit(0);
}

static bool key_test_handle(char);

static contents key_test(new mode("Key Test", key_test_handle));

static bool key_test_handle(char other) {
    move(key_test.y, key_test.x);

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

void key_test_command(contents& cont, boost::optional<int>) {
    key_test.refresh = false;
    key_test.y = 1;
    key_test.x = 1;
    move(0,0);
    printw("[Key test: type anything]");
    cont = key_test;
}
