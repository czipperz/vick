/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

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
std::shared_ptr<change>
quit_command(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Replaces the character at point with another one prompted
 * for.
 */
std::shared_ptr<change>
replace_character(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Removes the character at point.
 */
std::shared_ptr<change>
remove_character(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Prints the results of a number of ncurses builtin function
 * calls.
 */
std::shared_ptr<change>
color_test_command(contents&, boost::optional<int> = boost::none);
}

#endif
