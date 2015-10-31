#ifndef HEADER_GUARD_CHANGE_H
#define HEADER_GUARD_CHANGE_H

#include <boost/optional.hpp>
#include <functional>
#include <string>
#include <vector>
#include <memory>

class contents;

/*!
 * \file change.hh
 *
 * \brief Defines the change class and the undo_change(),
 * redo_change(), and reapply_change() functions.
 */

/*!
 * \class change change.hh "../../../src/change.hh"
 * \brief Represents a change from one \c contents to another
 *
 * The change class represents a change from one \c contents to
 * another.  It is basically a
 * \code{.cpp}
 * std::pair < std::function<void(contents&)>, std::function<void(contents&)> >
 * \endcode
 * but allows you to link two changes together using
 * \code{.cpp}
 * operator>>
 * \endcode
 *
 * You can link them together and put them in random places in the
 * undo tree/list.
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
};

/*!
 * \brief Undoes the change on top of the stack, or pops off another
 * if called again
 *
 * ----------
 * | ------ |
 * | before |
 * | after  |
 * | ------ |
 * ----------
 */
boost::optional<std::shared_ptr<change> >
undo_change(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Redoes the change on top of the stack, or climbs back on it 
 * Deletes anything after current
 *
 * ----------
 * | ------ |
 * | after  |
 * | before |
 * | ------ |
 * ----------
 */
boost::optional<std::shared_ptr<change> >
redo_change(contents&, boost::optional<int> = boost::none);

/*!
 * \brief Reapplies the current change on the current position
 * Deletes anything after current
 *
 * -----------------------
 * | current (reapplied) |
 * | current             |
 * | ------------------- |
 * -----------------------
 */
boost::optional<std::shared_ptr<change> >
reapply_change(contents&, boost::optional<int> = 0);

#endif
