/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_VISUAL_H
#define HEADER_GUARD_VISUAL_H

#include <string>
#include "contents.hh"

namespace vick {

/*!
 * \file visual.hh
 * \brief Convert an index location to its graphical location.
 *
 * \see TAB_SIZE
 */

/*!
 * \brief Converts an index location to its graphical location.
 *
 * This inverts `from_visual()`
 *
 * \pre x < cont.size()
 *
 * This statement will always be true:
 *
 * \code{.cpp}
 * to_visual("\thi", 1) == TAB_SIZE
 * \endcode
 */
move_t to_visual(const std::string& cont, move_t x);

/*!
 * \brief Converts a graphical location to its index location.
 *
 * This inverts `to_visual()`
 *
 * \post result < cont.size()
 *
 * This statement will always be true:
 *
 * \code{.cpp}
 * from_visual("\thi", TAB_SIZE) == 1
 * \endcode
 */
move_t from_visual(const std::string& cont, move_t x);
}

#endif
