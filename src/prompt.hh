#ifndef HEADER_GUARD_PROMPT_H
#define HEADER_GUARD_PROMPT_H

#include <string>

/*!
 * \brief Prompts the user for a message on the bottom of the screen.
 *
 * This method does not modify the buffer in any way.  It will start
 * to use \c show_message and \c print_contents shortly.
 */
std::string prompt(const std::string& message);

#endif
