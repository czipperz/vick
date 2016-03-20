#ifndef HEADER_GUARD_VISUAL_H
#define HEADER_GUARD_VISUAL_H

#include <string>

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
 * This statement will always be true:
 *
 * \code{.cpp}
 * to_visual("\thi", 1) == TAB_SIZE
 * \endcode
 */
int to_visual(const std::string& cont, int x);
/*!
 * \brief Converts a graphical location to its index location.
 *
 * This inverts `to_visual()`
 *
 * This statement will always be true:
 *
 * \code{.cpp}
 * from_visual("\thi", TAB_SIZE) == 1
 * \endcode
 */
int from_visual(const std::string& cont, int x);

}

#endif
