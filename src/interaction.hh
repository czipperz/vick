/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_INTERACTION_H
#define HEADER_GUARD_INTERACTION_H

#include <vector>

namespace vick {

/*!
 * \file interaction.hh
 * \brief Safe interaction with the visual environment
 *
 * The user shouldn't be using `ncurses.h` to control visual elements
 * as the editor will soon be using a graphical output.
 */


namespace attributes {

/*!
 * \brief Allows user to define what attributes should be displayed on
 * a piece of text.
 */
enum type {
    underline,
    bold,
    italic,
};
}

class scoped_attribute {
    std::vector<attributes::type> _old;

public:
    scoped_attribute(std::vector<attributes::type> _new);
    ~scoped_attribute();
};

}

#endif
