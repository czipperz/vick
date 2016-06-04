#ifndef HEADER_GUARD_PRINT_CONTENTS_H
#define HEADER_GUARD_PRINT_CONTENTS_H

#include "contents.hh"

namespace vick {
/*!
 * \brief Clears the screen and prints out the buffer.
 *
 * Uses `get_window_dimensions` to determine which parts of the buffer
 * to show.
 *
 * \param [in,out] contents The buffer to be displayed.  The
 * `y_offset` variable may be changed.  The hooks registered to after
 * print_contents are called on this contents.
 */
void print_contents(contents& contents);

// /*!
//  * \brief Clears the screen and prints out the buffer.
//  *
//  * Uses `get_window_dimensions` to determine which parts of the buffer
//  * to show.
//  *
//  * \param [in,out] contents The buffer to be displayed.  The only
//  *                          part of contents that can be changed is
//  *                          the `y_offset` variable.
//  */
// void print_contents(std::vector<contents>& contents);
}

#endif
