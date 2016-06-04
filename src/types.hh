/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_TYPES_H
#define HEADER_GUARD_TYPES_H

#include <cstddef>
#include <type_traits>

namespace vick {

/*!
 * \file types.hh
 *
 * \brief Defines `ssize_t`, `move_t{,s,u}`.
 */

/*!
 * \brief Define `ssize_t` so can use it on non-POSIX platforms.
 */
using ssize_t = typename std::make_signed<std::size_t>::type;

/*!
 * \brief Define `move_t` so that code can be more descriptive and
 * can change it from one place.
 */
using move_t = std::size_t;

/*!
 * \brief Define `move_ts` to be a signed version of `move_t`
 *
 * \see move_t
 */
using move_ts = typename std::make_signed<move_t>::type;

/*!
 * \brief Define `move_tu` to be an unsigned version of `move_t`
 *
 * \see move_t
 */
using move_tu = typename std::make_unsigned<move_t>::type;
}

#endif
