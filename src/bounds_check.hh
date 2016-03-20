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
