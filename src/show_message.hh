#ifndef HEADER_GUARD_SHOW_MESSAGE_H
#define HEADER_GUARD_SHOW_MESSAGE_H

#include <string>

/*!
 * \file show_message.hh
 *
 * \brief Controls showing a message on the bottom line of the screen
 */

/*!
 * \brief Controls whether a message has being shown this print cycle
 *
 * Allows the program to detect if someone else has already shown a
 * message, so they don't override someone else's message.
 */
extern bool showing_message;

/*!
 * \brief Immediately reshows the last message shown.
 *
 * The last message shown is just the last message passed to
 * show_message().
 *
 * \see add_hook()
 * \see proc_hook()
 */
void hook_show_message();
/*!
 * \brief Displays the message argument on the last line of the screen.
 *
 * This sets up hook_show_message() to work with this message.
 *
 * \param message The message to be displayed.
 */
void show_message(std::string message);
/*!
 * \brief Displays an empty string as a message on the last line of the screen.
 *
 * This sets up hook_show_message() to display nothing.
 */
void clear_message();

#endif
