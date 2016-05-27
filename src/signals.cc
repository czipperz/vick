/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <ncurses.h>
#include <csignal>
#include <cstdlib>

#include "signals.hh"

extern "C" {
static void myexit(int i) {
    endwin();
    SIG_DFL(i);
}
}

namespace vick {

void setup_signal_handling() {
    signal(SIGABRT, myexit);
    signal(SIGFPE, myexit);
    signal(SIGILL, myexit);
    signal(SIGINT, myexit);
    signal(SIGSEGV, myexit);
    signal(SIGTERM, myexit);
}
}
