/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

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
std::shared_ptr<change>
open_file_i(contents& contents, boost::optional<int> = boost::none);

/*!
 * \brief Loads a file specified into the buffer specified.
 */
std::shared_ptr<change>
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
