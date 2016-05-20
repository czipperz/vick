/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_BOUNDS_CHECK_H
#define HEADER_GUARD_BOUNDS_CHECK_H

#include "contents.hh"

namespace vick {

/*!
 * \file bounds_check.hh
 *
 * \brief Bounds check the contents buffer.
 */

/*!
 * \brief Makes sure that the cursor is inside the buffer.  It will
 * also properly initialize the buffer (by adding an empty line if the
 * contents are empty)
 */
void bounds_check(contents&);
}

#endif
