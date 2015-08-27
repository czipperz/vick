#include <vector>
#include <string>
#include <stdlib.h>
#include <ncurses.h>
#include "class_contents.hh"

void quit_command(const std::vector<std::string>&) {
    endwin();
    exit(0);
}

void key_test_command(const std::vector<std::string>&) {
    contents* cont(new contents());
    // cont->m.listeners[' '] = hi;
}
