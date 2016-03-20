#ifndef HEADER_GUARD_CHANGE_H
#define HEADER_GUARD_CHANGE_H

#include <boost/optional.hpp>
#include <functional>
#include <string>
#include <vector>
#include <memory>

namespace vick {

class contents;

/*!
 * \file change.hh
 *
 * \brief Defines the change class, representing a change from one
 * `contents` to another.
 */

/*!
 * \class change change.hh "../../../src/change.hh"
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
    virtual ~change()
    {
    }

    /*!
     * \brief Return true if you edit in any way anything but the x and y
     * coordinate
     */
    virtual bool is_overriding() = 0;

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
    virtual std::shared_ptr<change> regenerate(const contents&) const = 0;

    /*!
     * \brief Calls regenerate and then calls redo on the result and
     * returns the regenerated change.
     */
    std::shared_ptr<change> regenerate_and_apply(contents& cont);
};

}

#endif
