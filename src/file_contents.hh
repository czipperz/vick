/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_FILE_CONTENTS_H
#define HEADER_GUARD_FILE_CONTENTS_H

#include <locale>
#include <string>
#include <vector>
#include "configuration.hh"
#include "contents.hh"

namespace vick {

/*!
 * \file file_contents.hh
 * \brief Defines the init(), get_contents(), and print_contents()
 * methods.
 */

/*!
 * \brief Sets up the editor initally and calls loop().
 */
void init(int argc, char** argv);

/*!
 * \brief Returns the contents where the cursor currently is.
 */
contents& get_contents();

/*!
 * \brief Analyzes the buffer, starting at `y_offset`, describing
 * how much will fit on screen.
 *
 * \param [out] firsty the first line that can be shown.
 * \param [out] lasty the last line that can be shown.
 * \param [out] lastx the last x value of the `lasty` line that can be
 *                    shown.
 */
void get_window_dimensions(const contents&, move_t& firsty,
                           move_t& lasty, move_t& lastx);

/*!
 * \brief Describes the size of a single character on the screen.
 *
 * \param x The current x value - used if a tab character is
 *          encountered to determine its size.
 */
inline move_t char_size(char c, move_t x,
                        const std::locale& locale = std::locale()) {
    if (c == '\t') {
        return TAB_SIZE - (x % TAB_SIZE);
    } else if (std::iscntrl(c, locale)) {
        return 2;
    } else {
        return 1;
    }
}

/*!
 * \brief Describes the size of a line on screen.
 *
 * Essentially maps `char_size` over the line and then accumulates the
 * results.
 */
inline move_t line_size(const std::string& line,
                        const std::locale& locale = std::locale()) {
    move_t sum = 0;
    const auto end = std::end(line);
    for (auto it = std::begin(line); it != end; ++it) {
        sum += char_size(*it, sum, locale);
    }
    return sum;
}
}

#endif
