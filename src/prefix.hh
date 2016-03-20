#ifndef HEADER_GUARD_PREFIX_H
#define HEADER_GUARD_PREFIX_H

#include <map>
#include <functional>
#include <boost/optional.hpp>

#include "change.hh"

namespace vick {

/*!
 * \file prefix.hh
 *
 * \brief Defines the prefix class, the standard way to make a prefix key.
 */

class contents;

/*!
 * \class prefix prefix.hh "../../../src/prefix.hh"
 * \brief The standard way to make a prefix key.
 *
 * A prefix key is one that presents a multitude of different options
 */
class prefix {
private:
    std::shared_ptr<std::map<char, std::function<boost::optional<std::shared_ptr<change> >
                                                 (contents&, boost::optional<int>)> > > map;
    /*! Used exclusively for function lookup failures (unbound keys) */
    std::string message;

public:
    /*!
     * \param message The message to display when a lookup failure
     * occures.  This will happen when the key they typed was unbound.
     * Message will be displayed with a dash appended.
     */
    prefix(std::string message);

    /*!
     * \brief Associates a character with a function.
     */
    void
    push_back(char, std::function<boost::optional<std::shared_ptr<change> >
                                  (contents&, boost::optional<int>)>);

    /*!
     * \brief Prompts for a character while displaying the history given in
     * the constructor, then calls the function associated with that
     * character.
     *
     * To associate a character with a function, use push_back().
     */
    boost::optional<std::shared_ptr<change> >
    operator()(contents&, boost::optional<int>);

    /*!
     * \brief Converts this object to a std::function.
     *
     * operator()() will be called when operator()() is used on the created
     * std::function object.
     */
    operator std::function<boost::optional<std::shared_ptr<change> >
                           (contents&, boost::optional<int>)>();
};

}

#endif
