/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_INT_TO_STR_H
#define HEADER_GUARD_INT_TO_STR_H

#include <string>
#include <vector>

namespace vick {

/*!
 * \file inter_space.hh
 * \brief Defines the `inter_space()` function.
 */

/*!
 * \brief Concatenates a list by inserting a space between each
 * element.
 */
std::string inter_space(const std::vector<std::string>& vec);
}

#endif
