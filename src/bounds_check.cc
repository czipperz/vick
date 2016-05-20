/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bounds_check.hh"

namespace vick {

void bounds_check(contents& contents) {
    if (contents.cont.empty()) {
        contents.cont.push_back("");
        contents.y = 0;
        contents.x = 0;
        return;
    }
    // if (contents.y < 0) contents.y = 0;
    // else
    if (contents.y >= contents.cont.size())
        contents.y = contents.cont.size() - 1;
    // if (contents.x < 0) contents.x = 0;
    // else
    if (contents.x >= contents.cont[contents.y].length())
        contents.x = contents.cont[contents.y].length() - 1;
}
}
