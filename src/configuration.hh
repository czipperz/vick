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
 * \brief The horizontal space a tab character should take up
 */
extern int TAB_SIZE;

/*!
 * \brief The function to be called when an edit wants to be pushed to
 * the stack.
 */
extern void (*PUSH_BACK_CHANGE)(contents&,std::shared_ptr<change>);

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
void add_commands(std::map<
    std::string, std::function<boost::optional<std::shared_ptr<change> >(
                     contents&, boost::optional<int>)> >&);

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
 * \brief This method is called at the very beginning of the editor,
 * after ncurses has started but before even buffer is loaded
 */
void init_conf();

}

#endif
