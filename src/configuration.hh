/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_Configuration_H
#define HEADER_GUARD_Configuration_H

#include "contents.hh"

namespace vick {

/*!
 * \file configuration.hh
 * \brief The file that defines what user customizable features exist
 */

/*!
 * \brief Hitting this key should stop most commands mid process,
 * however its up to the commands themselves to handle it!
 */
extern char QUIT_KEY;

/*!
 * \brief The horizontal space a tab character should take up.
 */
extern move_t TAB_SIZE;

/*!
 * \brief The number of lines reserved for the bottom of each window.
 */
extern move_t BOTTOM_HEIGHT;

/*!
 * \brief The function to be called when an edit wants to be pushed to
 * the stack.
 */
extern void (*PUSH_BACK_CHANGE)(contents&, std::shared_ptr<change>);

/*!
 * \brief Controls whether colors are used <i>at all</i>
 */
bool use_colors();

/*!
 * \brief Assigns bindings to global mappings
 * \see global_insert_map
 * \see global_normal_map
 */
void add_listeners();

/*!
 * \brief Binds commands to be called by command_executor()
 */
void add_commands();

/*!
 * \brief Characters that aren't word characters or whitespace
 *
 * These are used in the various move function based on words.  They
 * distinguish what is a word character.  For example, to only break
 * words based on whitespace, ampersands, and equals signs, use:
 *
 * \code{.cpp}
 * DELIMINATORS = "&=";
 * \endcode
 *
 * in your configuration.cc file.
 */
extern std::string DELIMINATORS;

/*!
 * \brief Characters that match with one another
 *
 * These are used in the `mvmatch()` function (as of now).  They
 * distiguish what characters should match with another.  For example,
 * to have `{` match with `}` and `(` match with `)` <i>only</i>, then
 * use:
 *
 * \code{.cpp}
 * MATCHES = "{}()";
 * \endcode
 *
 * in your configuration.cc file.
 */
extern std::string MATCHES;

/*!
 * \brief This method is called at the very beginning of the editor,
 * after ncurses has started but before even buffer is loaded
 */
void init_conf();
}

#endif
