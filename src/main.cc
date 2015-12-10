#include <algorithm>
#include <fstream>
#include <iterator>
#include <ncurses.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "file_contents.hh"
#include "key_listeners.hh"
#include "prompt.hh"
#include "signals.hh"

int main(int argc, char** argv) {
    using namespace vick;

    argc--;argv++;

    setup_signal_handling();

    initscr();
    noecho();
    raw();

    if(use_colors()) {
        start_color();
    }

    init_conf();

    init(argc, argv);
    loop();

    endwin();
    return 0;
}
