#ifndef HEADER_GUARD_CHANGE_H
#define HEADER_GUARD_CHANGE_H

#include <functional>
#include <string>
#include <vector>

class contents;

/*!
 * \file change.hh
 *
 * \brief Defines the change class
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
class change {
  private:
    std::function<void(contents&)> _redo, _undo;

  public:
    /*!
     * \brief Constructs a change
     *
     * \param redo The function to be called when \c redo is called
     * \param undo The function to be called when \c undo is called
     *
     * \see change::redo()
     * \see change::undo()
     */
    change(std::function<void(contents&)> redo, std::function<void(contents&)> undo);

    /*!
     * \brief Links two changes together
     *
     * Example:
     *
     * \code{.cpp}
     * mvd >> mvsot >> mvf
     * \endcode
     *
     * would move to the second non whitespace character on the next
     * line <em>when, if ever it is called</em>.
     *
     * If you then call the undo function, it would retrace out in the
     * opposite direction.
     */
    change operator>>(const change&) const;

    /*!
     * \brief Calls the redo variable
     *
     * \see change()
     */
    void redo(contents&) const;
    /*!
     * \brief Calls the undo variable
     *
     * \see change()
     */
    void undo(contents&) const;
};

#endif
