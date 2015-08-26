#include <map>
#include <string>
#include <vector>

#include "basic_commands.hh"
#include "command_listeners.hh"
#include "move.hh"
#include "prefix_g.hh"
#include "configuration.hh"

const int TAB_SIZE = 8;

const std::string DELIMINATORS = "!@#$%^&*()-_=+[]{};:<>,.'\"/?`~| \t";

void add_listeners(std::map<char,void (*)()>& listeners) {
    listeners['j'] = mvb1;
    listeners['k'] = mvd1;
    listeners['l'] = mvu1;
    listeners[';'] = mvf1;

    listeners['^'] = mvsol;
    listeners['0'] = mvsot;
    listeners['$'] = mveol;
    listeners[':'] = command_executor;

    listeners['g'] = prefix_g;
    listeners['G'] = mveop;
    listeners['w'] = mvf1w;
    listeners['b'] = mvb1w;
}

void add_commands(std::map<std::string,
                           void (*)(const std::vector<std::string>&)>&
                  commandMap) {
    commandMap["q"]     = quit_command;
    commandMap["quit"]  = quit_command;
}
