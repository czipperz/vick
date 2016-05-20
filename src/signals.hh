/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_SIGNALS_H
#define HEADER_GUARD_SIGNALS_H

namespace vick {

/*!
 * \file signals.hh
 * \brief Defines the `setup_signal_handling()` function.
 */

/*!
 * \brief This will make all system signals end the ncurses session
 * then do the default behavior.
 *
 * This is useful as it will cause segfaults to properly be handled
 * instead of making the terminal extremely unreadable.
 *
 * \see <csignal>
 * \see <signal.h>
 */
void setup_signal_handling();
}

#endif
