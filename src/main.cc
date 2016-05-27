/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <ncurses.h>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "configuration.hh"
#include "file_contents.hh"
#include "key_listeners.hh"
#include "prompt.hh"
#include "signals.hh"

int main(int argc, char** argv) {
    using namespace vick;

    argc--;
    argv++;

    setup_signal_handling();

    initscr();
    noecho();
    raw();

    if (use_colors()) {
        start_color();
    }

    init_conf();

    init(argc, argv);
    loop();

    endwin();
    return 0;
}
