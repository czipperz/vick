/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <ncurses.h>
#include <stdlib.h>
#include <boost/optional.hpp>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "command_listeners.hh"
#include "configuration.hh"
#include "inter_space.hh"
#include "key_aliases.hh"
#include "prompt.hh"
#include "show_message.hh"

namespace vick {

static std::map<std::string,
                std::function<boost::optional<std::shared_ptr<
                    change> >(contents&, boost::optional<int>)> >
    commandMap;

boost::optional<std::shared_ptr<change> >
command_executor(contents& cont, boost::optional<int> times) {
    {
        static bool init = true;
        if (init) {
            add_commands(commandMap);
            init = false;
        }
    }

    attron(COLOR_PAIR(1));
    boost::optional<std::string> pr = prompt(":");
    attroff(COLOR_PAIR(1));
    if (not pr or pr->empty()) {
        clear_message();
        return boost::none;
    }
    auto command = commandMap.find(*pr);
    if (command == commandMap.end()) {
        show_message(std::string("Unrecognized command: ") + *pr);
        return boost::none;
    } else {
        return command->second(cont, times);
    }
}
}
