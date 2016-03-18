#ifndef HEADER_GUARD_BASIC_COMMANDS_H
#define HEADER_GUARD_BASIC_COMMANDS_H

#include "contents.hh"

namespace vick {

/*!
 * \file basic_commands.hh
 *
 * \brief A collection of simple commands that are part of the main
 * project as for now.
 */

/*!
 * \brief The command that signals a full editor quit.
 */
boost::optional<std::shared_ptr<change> >
quit_command(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Replaces the character at point with another one prompted for.
 */
boost::optional<std::shared_ptr<change> >
replace_character(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Removes the character at point.
 */
boost::optional<std::shared_ptr<change> >
remove_character(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Prints the results of a number of ncurses builtin function calls.
 */
boost::optional<std::shared_ptr<change> >
color_test_command(contents&, boost::optional<int> = boost::none);

}

#endif
