/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "change.hh"

namespace vick {

std::shared_ptr<change> change::regenerate_and_apply(contents& cont) {
    auto x = regenerate(cont);
    x->redo(cont);
    return x;
}
}
