#ifndef HEADER_GUARD_BASIC_COMMANDS_H
#define HEADER_GUARD_BASIC_COMMANDS_H

#include "contents.hh"

/*!
 * \file basic_commands.hh
 *
 * \brief A collection of simple commands that are part of the main
 * project as for now.
 */

/*!
 * \brief The command that signals a full editor quit.
 */
void quit_command(contents&, boost::optional<int>);
/*!
 * \brief Switches into key_test mode.  Don't use this for anything.
 */
void key_test_command(contents&, boost::optional<int>);
/*!
 * \brief Replaces the character at point with another one prompted for.
 */
void replace_character(contents&, boost::optional<int>);

#endif
