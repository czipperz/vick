#ifndef HEADER_GUARD_OPEN_FILE_H
#define HEADER_GUARD_OPEN_FILE_H

#include "contents.hh"

namespace vick {

/*!
 * \file open_file.hh
 * \brief Allows for the user to open a file, loading it into a
 * buffer.
 */

/*!
 * \brief For interactive use!  Loads a file prompted interactively
 * into the buffer given.
 */
boost::optional<std::shared_ptr<change> >
open_file_i(contents& contents, boost::optional<int> = boost::none);

/*!
 * \brief Loads a file specified into the buffer specified.
 */
boost::optional<std::shared_ptr<change> >
open_file(contents& contents, std::string file);

/*!
 * \brief Loads a file specified and returns the captured contents.
 *
 * These are roughly equivalent:
 *
 * \code{.cpp}
 * contents c = open_file(file);
 * \endcode
 *
 * \code{.cpp}
 * contents c;
 * open_file(contents, file);
 * \endcode
 */
contents open_file(std::string file);
}

#endif
