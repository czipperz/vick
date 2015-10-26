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

static std::map<std::string,
                std::function < boost::optional< std::shared_ptr<change> >
                                    (contents&, boost::optional<int>) > >
    commandMap;
static bool fin = false;

static std::vector<std::string> spaciate(const std::string&);

boost::optional< std::shared_ptr<change> > command_executor(contents& cont, boost::optional<int> times) {
    if(!fin) { add_commands(commandMap); fin = true; }

    attron(COLOR_PAIR(1));
    std::string pr = prompt(":");
    attroff(COLOR_PAIR(1));
    if(pr == "") {
        clear_message();
        return boost::none;
    }
    std::vector<std::string> args = spaciate(pr);
    std::string name = args[0];
    args.erase(args.begin());
    if(commandMap.count(name)) {
        return commandMap[name](cont,times);
    } else if(args.size() != 0) {
        show_message(std::string("Unrecognized command: ") + name +
                     " with args: " + inter_space(args));
    } else {
        show_message(std::string("Unrecognized command: ") + name +
                     " with null args.");
    }
    return boost::none;
}

static std::vector<std::string> spaciate(const std::string& tospace) {
    std::vector<std::string> spaced;
    std::string cur;
    for(unsigned int i = 0; i < tospace.length(); i++) {
        if(tospace[i] == ' ' || tospace[i] == '\t') {
            if(cur.length()) {
                spaced.push_back(cur);
                cur = "";
            }
        } else {
            cur += tospace[i];
        }
    }
    if (cur.length()) spaced.push_back(cur);
    return spaced;
}
