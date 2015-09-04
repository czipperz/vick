#include <vector>
#include <string>
#include <stdlib.h>
#include <ncurses.h>
#include "contents.hh"

void quit_command(contents&, boost::optional<int>) {
    endwin();
    exit(0);
}

void key_test_command(contents&, boost::optional<int>) {
    contents cont;
    // cont->m.listeners[' '] = hi;
}
