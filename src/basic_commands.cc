#include <vector>
#include <string>
#include <stdlib.h>
#include <ncurses.h>

void quit_command(const std::vector<std::string>&) {
    endwin();
    exit(0);
}
