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
 * \brief Defines the prefix class, the standard way to make a prefix
 * key.
 */

/*!
 * \class prefix prefix.hh "../../../src/prefix.hh"
 * \brief The standard way to make a prefix key.
 *
 * A prefix key is one that presents a multitude of different options
 */
class prefix {
private:
    std::shared_ptr<std::map<
        char, std::function<boost::optional<std::shared_ptr<
                  change> >(contents&, boost::optional<int>)> > > map;
    /*!
     * \brief Used exclusively for function lookup failures (unbound
     * keys)
     */
    std::string history;

public:
    /*!
     * \param history The key binding that caused this prefix to be
     * ran.  It will be displayed with a dash and the key the user
     * pressed that caused this error.
     */
    prefix(std::string history);

    /*!
     * \brief Associates a character with a function.
     */
    void
    push_back(char,
              std::function<boost::optional<std::shared_ptr<change> >(
                  contents&, boost::optional<int>)>);

    /*!
     * \brief Prompts for a character while displaying the history
     * given in the constructor, then calls the function associated
     * with that character.
     *
     * To associate a character with a function, use push_back().
     */
    boost::optional<std::shared_ptr<change> >
    operator()(contents&, boost::optional<int>);

    /*!
     * \brief Converts this object to a std::function.
     *
     * `operator()()` will be called when `operator()()` is used on
     * the created `std::function` object.
     */
    operator std::function<boost::optional<std::shared_ptr<change> >(
        contents&, boost::optional<int>)>();
};
}

#endif
