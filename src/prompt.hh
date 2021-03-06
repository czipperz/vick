/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_PROMPT_H
#define HEADER_GUARD_PROMPT_H

#include <boost/optional.hpp>
#include <string>

namespace vick {

/*!
 * \file prompt.hh
 * \brief Defines the prompt function that allows you to prompt for a
 * string using a message
 */

/*!
 * \brief Prompts the user for a message on the bottom of the screen.
 *
 * This method does not modify the buffer in any way.  It will start
 * to use `show_message` and `print_contents` shortly.
 */
boost::optional<std::string> prompt(const std::string& message);

/*!
 * \brief Prompts the user for a message on the bottom of the screen.
 * Only allows the reading of characters `y` or `n`.
 */
boost::optional<bool> prompt_yn(const std::string& message);

/*!
 * \brief Prompts the user for a message on the bottom of the screen.
 * Only allows the reading of the strings `yes` or `no`.
 */
boost::optional<bool> prompt_yes_no(const std::string& message);

/*!
 * \brief Runs the function given continuously until it returns a
 * "truthy" value, at which point it will return that value
 * dereferenced.
 *
 * This acts as a way to take a `boost::optional<T>` and turn it into
 * a `T` deterministically.  This assumes the function given is non
 * pure or side effect driven.
 */
template <typename Fun, typename... Xs>
auto repeat_remove_optional(Fun f, std::string prompt, Xs&&... xs)
    -> decltype(*f(prompt, xs...)) {
    auto x = f(prompt, xs...);
    if (x)
        return *std::move(x);
    prompt += "(Required!) ";
    while (true) {
        x = f(prompt, xs...);
        if (x)
            return *std::move(x);
    }
}
}

#endif
