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
