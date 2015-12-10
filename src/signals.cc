#include <csignal>
#include <ncurses.h>
#include <cstdlib>

#include "signals.hh"

extern "C" void myexit(int i) {
    endwin();
    SIG_DFL(i);
}

namespace vick {

void setup_signal_handling() {
    signal(SIGABRT, myexit);
    signal(SIGFPE,  myexit);
    signal(SIGILL,  myexit);
    signal(SIGINT,  myexit);
    signal(SIGSEGV, myexit);
    signal(SIGTERM, myexit);
}

}
