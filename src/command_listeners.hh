#ifndef HEADER_GUARD_COMMAND_LISTENERS_H
#define HEADER_GUARD_COMMAND_LISTENERS_H

#include "contents.hh"

namespace vick {

/*!
 * \file command_listeners.hh
 * \brief Defines the command_executor() function.
 */

/*!
 * \brief Executes a command by name (Vim's `:`, Emacs's `M-x`)
 *
 * Executes a relevant command based on user input.  All commands are
 * bound in <i>configuration.cc</i>
 *
 * \see configuration.hh
 */
boost::optional<std::shared_ptr<change> >
command_executor(contents& cont, boost::optional<int> times);
}

#endif
