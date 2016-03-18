#ifndef HEADER_GUARD_FILE_CONTENTS_H
#define HEADER_GUARD_FILE_CONTENTS_H

#include <vector>
#include <string>
#include "contents.hh"

namespace vick {

/*!
 * \file file_contents.hh
 * \brief Defines the init(), get_contents(), and print_contents() methods.
 */

/*!
 * \brief Sets up the editor initally and calls loop().
 */
void init(int argc, char** argv);

/*!
 * \brief Returns the contents where the cursor currently is
 */
contents& get_contents();

/*!
 * \brief Clears the screen and prints out the buffer.
 *
 * Uses `get_window_dimensions` to determine which parts of the buffer
 * to show.
 *
 * \param [in, out] contents The buffer to be displayed.  The only
 *                           part of contents that can be changed is
 *                           the `y_offset` variable.
 */
void print_contents(contents&);

}

#endif
