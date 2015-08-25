#include <iostream>
#include <ncurses.h>
#include <map>
#include <string>
#include <stdlib.h>
#include <vector>

#include "configuration.hh"
#include "int_to_str.hh"
#include "key_aliases.hh"
#include "show_message.hh"
#include "prompt.hh"

static std::map<std::string,
                void (*)(const std::vector<std::string>&)>
    commandMap;
static bool fin = false;

static std::vector<std::string>* spaciate(const std::string&);

void command_executor() {
    if(!fin) { add_commands(commandMap); fin = true; }
    std::string pr = prompt(":");
    if(pr == "") return;
    std::vector<std::string>* args = spaciate(pr);
    std::string name = (*args)[0];
    args->erase(args->begin());
    if(commandMap.count(name)) commandMap[name](*args);
    else show_message((std::string("Unrecognized command: ") + name +
                       " with args: " + inter_space(args)).c_str());
}

static std::vector<std::string>* spaciate(const std::string& tospace) {
    std::vector<std::string>* spaced = new std::vector<std::string>();
    std::string cur;
    for(unsigned int i = 0; i < tospace.length(); i++) {
        if(spaced[i] == ' ' || spaced[i] == '\t') {
            
        }
    }
}
