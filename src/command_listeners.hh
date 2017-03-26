/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_COMMAND_LISTENERS_H
#define HEADER_GUARD_COMMAND_LISTENERS_H

#include "contents.hh"

namespace vick {

/*!
 * \file command_listeners.hh
 * \brief Defines the command_executor() function.
 */

/*!
 * \brief The global binding of commands to functions.
 */
extern std::map<std::string,
                std::function<std::shared_ptr<
                    change>(contents&, boost::optional<int>)> >
    global_command_map;

/*!
 * \brief Executes a command by name (Vim's `:`, Emacs's `M-x`)
 *
 * Executes a relevant command based on user input.  All commands are
 * bound in <i>configuration.cc</i>
 *
 * \see configuration.hh
 */
std::shared_ptr<change>
command_executor(contents& cont, boost::optional<int> times);
}

#endif
