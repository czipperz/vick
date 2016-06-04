/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <string>

#include "configuration.hh"
#include "visual.hh"

namespace vick {

move_t from_visual(const std::string& cont, move_t x) {
    if (cont.empty())
        return 0;
    move_t count = 0, til = 0;
    move_t numTab = 0;
    for (size_t i = 0; i < cont.length(); i++) {
        size_t len;
        if (cont[i] == '\t') {
            len = TAB_SIZE - 1 - til;
            til = 0;
            numTab++;
        } else {
            len = 1;
            til++;
            til %= TAB_SIZE;
        }
        count += len;
        if (count + numTab > x)
            return i;
    }
    return -1;
}

move_t to_visual(const std::string& cont, move_t x) {
    move_t til = 0, xx = move_t(-1);
    for (std::string::const_iterator i = cont.begin();
         i <= cont.begin() + x; ++i) {
        if (*i == '\t') {
            xx += TAB_SIZE - til;
            til = 0;
        } else {
            til++;
            til %= TAB_SIZE;
            xx++;
        }
    }
    return xx;
}
}
