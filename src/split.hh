/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_SPLIT_H
#define HEADER_GUARD_SPLIT_H

#include <string>
#include <vector>

namespace vick {

/*!
 * \file split.hh
 * \brief Defines split(), which splits a string by a given char into
 * a vector.
 */

/*!
 * \brief Splits the given string by a given char into a vector.
 *
 * For example,
 * \code
 * split("\nhi\nbye", '\n') == {"", "hi", "bye"};
 * split("\r\nhi\r\nbye", '\n') == {"\r", "hi\r", "bye"};
 * split("\nhi\nbye\n", '\n') == {"", "hi", "bye", ""};
 * split("\r\nhi\r\nbye\r\n", '\n') == {"\r", "hi\r", "bye\r", ""};
 * \endcode
 */
std::vector<std::string>
split(const std::string& str, char delim);

/*!
 * \brief Splits the given string by line into a vector.  Accounts for
 * windows carriage return encodings.
 *
 * For example,
 * \code
 * split_by_line("\nhi\nbye") == {"", "hi", "bye"};
 * split_by_line("\r\nhi\r\nbye") == {"", "hi", "bye"};
 * split_by_line("\nhi\nbye\n") == {"", "hi", "bye", ""};
 * split_by_line("\r\nhi\r\nbye\r\n") == {"", "hi", "bye", ""};
 * \endcode
 */
std::vector<std::string>
split_by_line(const std::string& str);
}

#endif
