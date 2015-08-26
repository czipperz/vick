#include <iostream>
#include <map>
#include <ncurses.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "int_to_str.hh"
#include "key_aliases.hh"
#include "prompt.hh"
#include "show_message.hh"

static std::map<std::string,
                void (*)(const std::vector<std::string>&)>
    commandMap;
static bool fin = false;

static std::vector<std::string>* spaciate(const std::string&);

void command_executor() {
    if(!fin) { add_commands(commandMap); fin = true; }
    std::string pr = prompt(":");
    if(pr == "") {
        clear_message();
        return;
    }
    std::vector<std::string>* args = spaciate(pr);
    std::string name = (*args)[0];
    args->erase(args->begin());
    if(commandMap.count(name)) {
        commandMap[name](*args);
    } else if(args->size() != 0) {
        show_message((std::string("Unrecognized command: ") + name +
                      " with args: " + inter_space(args)).c_str());
    } else {
        show_message((std::string("Unrecognized command: ") + name +
                      " with null args.").c_str());
    }
    delete args;
}


#define _check \
    if(cur.length() != 0) {     \
        spaced->push_back(cur); \
        cur = ""; \
    }

static std::vector<std::string>* spaciate(const std::string& tospace) {
    std::vector<std::string>* spaced = new std::vector<std::string>();
    std::string cur;
    for(unsigned int i = 0; i < tospace.length(); i++) {
        if(tospace[i] == ' ' || tospace[i] == '\t') {
            _check;
        } else {
            cur += tospace[i];
        }
    }
    _check;
    return spaced;
}
#undef _check
