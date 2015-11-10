#ifndef HEADER_GUARD_SPLIT_H
#define HEADER_GUARD_SPLIT_H

#include <vector>
#include <string>

/*!
 * \file split.hh
 * \brief Defines split(), which splits a string by a given char into a vector.
 */

/*!
 * \brief Splits the given string by a given char into a vector.
 *
 * For example,
 * \code
 * split("\nhi\nbye", '\n') == {"", "hi", "bye"};
 * \endcode
 */
std::vector<std::string> split(const std::string& str, char delim);

#endif
