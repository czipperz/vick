#include <iostream>
#include <map>
#include <ncurses.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <functional>
#include <boost/optional.hpp>

#include "configuration.hh"
#include "key_aliases.hh"
#include "prompt.hh"
#include "show_message.hh"
#include "inter_space.hh"

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
