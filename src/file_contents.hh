#ifndef HEADER_GUARD_FILE_CONTENTS_H
#define HEADER_GUARD_FILE_CONTENTS_H

#include <vector>
#include <string>
#include "contents.hh"

/*!
 * \file file_contents.hh
 * \brief Defines the init(), get_contents(), and print_contents() methods.
 */

/*!
 * \brief Sets up the editor initally and calls loop().
 */
void      init(std::vector<std::string>);
/*!
 * \brief Returns the contents where the cursor currently is
 */
contents& get_contents();
/*!
 * \brief Clears the screen and prints out a contents
 */
void      print_contents(contents&);

#endif
