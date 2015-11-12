#ifndef HEADER_GUARD_INT_TO_STR_H
#define HEADER_GUARD_INT_TO_STR_H

#include <string>
#include <vector>

namespace vick {

/*!
 * \file inter_space.hh
 * \brief Defines the inter_space() function.
 */

/*!
 * \brief Concatenates a list by inserting a space between each
 * element.
 */
std::string inter_space(const std::vector<std::string>& vec);

}

#endif
