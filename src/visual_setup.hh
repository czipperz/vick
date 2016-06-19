/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_VISUAL_SETUP_H
#define HEADER_GUARD_VISUAL_SETUP_H

#include <ncurses.h>

namespace vick {
struct visual_setup {
    visual_setup() { initscr(); }
    ~visual_setup() { endwin(); }
};
}

#endif
