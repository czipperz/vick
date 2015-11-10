#ifndef HEADER_GUARD_PROMPT_H
#define HEADER_GUARD_PROMPT_H

#include <boost/optional.hpp>
#include <string>

/*!
 * \file prompt.hh
 * \brief Defines the prompt function that allows you to prompt for a string using a message
 */

/*!
 * \brief Prompts the user for a message on the bottom of the screen.
 *
 * This method does not modify the buffer in any way.  It will start
 * to use \c show_message and \c print_contents shortly.
 */
boost::optional<std::string> prompt(const std::string& message);

/*!
 * \brief Prompts the user for a message on the bottom of the screen.
 * Only allows the reading of characters `y` or `n`.
 */
bool prompt_yn(const std::string& message);

/*!
 * \brief Prompts the user for a message on the bottom of the screen.
 * Only allows the reading of the strings `yes` or `no`.
 */
bool prompt_yes_no(const std::string& message);

#endif
