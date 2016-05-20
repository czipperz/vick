/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_PREFIX_KEY_H
#define HEADER_GUARD_PREFIX_KEY_H

#include <boost/optional.hpp>

#include "contents.hh"

namespace vick {

/*!
 * \file prefix_key.hh
 *
 * \brief Defines the prefix_keys, the standard way of creating the
 * ``boost::optional<int>`` argument of every function application.
 *
 * These methods are intended to be only used interactively and never
 * from another method.  If you want to use a prefix_key from another
 * method, just apply it yourself.  These methods use keyboard input
 * so are impure by definition.
 */

/*!
 * \brief The key to be pressed after another that will multiply the
 * prefix argument by that amount.
 */
extern char prefix_key_times_ten;

/*!
 * \brief Multiplies the argument by ten and adds one and calls the
 * next function.
 *
 * If no argument is provided it will default to zero.
 */
boost::optional<std::shared_ptr<change> >
prefix_key_1(contents&, boost::optional<int>);

/*!
 * \brief Multiplies the argument by ten and adds two and calls the
 * next function.
 *
 * If no argument is provided it will default to zero.
 */
boost::optional<std::shared_ptr<change> >
prefix_key_2(contents&, boost::optional<int>);

/*!
 * \brief Multiplies the argument by ten and adds three and calls the
 * next function.
 *
 * If no argument is provided it will default to zero.
 */
boost::optional<std::shared_ptr<change> >
prefix_key_3(contents&, boost::optional<int>);

/*!
 * \brief Multiplies the argument by ten and adds four and calls the
 * next function.
 *
 * If no argument is provided it will default to zero.
 */
boost::optional<std::shared_ptr<change> >
prefix_key_4(contents&, boost::optional<int>);

/*!
 * \brief Multiplies the argument by ten and adds five and calls the
 * next function.
 *
 * If no argument is provided it will default to zero.
 */
boost::optional<std::shared_ptr<change> >
prefix_key_5(contents&, boost::optional<int>);

/*!
 * \brief Multiplies the argument by ten and adds six and calls the
 * next function.
 *
 * If no argument is provided it will default to zero.
 */
boost::optional<std::shared_ptr<change> >
prefix_key_6(contents&, boost::optional<int>);

/*!
 * \brief Multiplies the argument by ten and adds seven and calls the
 * next function.
 *
 * If no argument is provided it will default to zero.
 */
boost::optional<std::shared_ptr<change> >
prefix_key_7(contents&, boost::optional<int>);

/*!
 * \brief Multiplies the argument by ten and adds eight and calls the
 * next function.
 *
 * If no argument is provided it will default to zero.
 */
boost::optional<std::shared_ptr<change> >
prefix_key_8(contents&, boost::optional<int>);

/*!
 * \brief Multiplies the argument by ten and adds nine and calls the
 * next function.
 *
 * If no argument is provided it will default to zero.
 */
boost::optional<std::shared_ptr<change> >
prefix_key_9(contents&, boost::optional<int>);
}

#endif
