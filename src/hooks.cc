/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "hooks.hh"
#include <map>
#include <vector>

namespace vick {

void hook::proc(contents& contents) {
    for (auto& f : functions) {
        f(contents);
    }
}

void hook::add(void (*f)(contents&)) { functions.push_back(f); }

bool hook::remove(void (*f)(contents&)) {
    auto new_end = std::remove(functions.begin(), functions.end(), f);
    auto b = new_end != functions.end();
    functions.erase(new_end, functions.end());
    return b;
}

namespace hooks {
hook save;
hook refresh;
hook mode_enter;
hook open_file;
hook contents_created;
hook contents_deleted;
}
}
