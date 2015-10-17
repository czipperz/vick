#ifndef HEADER_GUARD_Configuration_H
#define HEADER_GUARD_Configuration_H

#include "contents.hh"

/*!
 * \file configuration.hh
 * \brief The file that defines what user customizable features exist
 */

/*!
 * \brief The horizontal space a tab character should take up
 */
extern const int TAB_SIZE;

/*!
 * \brief Assigns bindings to global mappings
 * \see global_insert_map
 * \see global_normal_map
 */
void add_listeners();

/*!
 * \brief Binds commands to be called by command_executor()
 */
void add_commands(
    std::map< std::string,
              std::function< boost::optional< std::shared_ptr<change> >
                                (contents&, boost::optional<int>)> >&);

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
extern const std::string DELIMINATORS;

#endif
