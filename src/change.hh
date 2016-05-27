/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_CHANGE_H
#define HEADER_GUARD_CHANGE_H

#include <boost/optional.hpp>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace vick {

class contents;

/*!
 * \file change.hh
 *
 * \brief Defines the change class, representing a change from one
 * `contents` to another.
 */

/*!
 * \class change change.hh "change.hh"
 * \brief Represents a change from one `contents` to another
 *
 * It allows for virtual dispath on undoing, redoing, and regeneration
 * of a textual edit to the buffer.  `undo` will put the contents in
 * the state it was before the edit.  `redo` will put the contents in
 * the state it was after the edit.  `regenerate` generates a new
 * change at the new position in the buffer, or acting on the new
 * buffer state that must be manually `redo`ne on the contents.
 *
 * \see contents
 */
struct change {
    virtual ~change() = default;

    /*!
     * \brief Return true if you edit the `contents`
     *
     * Basically allows controll over whether it should be "undone".
     */
    virtual bool is_overriding() const noexcept = 0;

    /*!
     * \brief Undoes this edit
     */
    virtual void undo(contents&) = 0;

    /*!
     * \brief Performs this edit again (Use after an undo)
     */
    virtual void redo(contents&) = 0;

    /*!
     * \brief Generates a change that will act over the new contents
     */
    virtual std::shared_ptr<change>
    regenerate(const contents&) const = 0;

    /*!
     * \brief Calls regenerate and then calls redo on the result and
     * returns the regenerated change.
     */
    std::shared_ptr<change> regenerate_and_apply(contents& cont);
};
}

#endif
