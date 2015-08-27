#include <map>
#include <string>
#include <vector>

#include "basic_commands.hh"
#include "command_listeners.hh"
#include "configuration.hh"
#include "mode.hh"
#include "move.hh"
#include "prefix_g.hh"

const int TAB_SIZE = 8;

const std::string DELIMINATORS = "!@#$%^&*()-_=+[]{};:<>,.'\"/?`~| \t";

void add_listeners() {
    global_normal_map['j'] = mvb1;
    global_normal_map['k'] = mvd1;
    global_normal_map['l'] = mvu1;
    global_normal_map[';'] = mvf1;

    global_normal_map['^'] = mvsol;
    global_normal_map['0'] = mvsot;
    global_normal_map['$'] = mveol;
    global_normal_map[':'] = command_executor;

    global_normal_map['G'] = mveop;
    global_normal_map['w'] = mvf1w;
    global_normal_map['b'] = mvb1w;

    setup_prefix_g();
}

void add_commands(std::map<std::string,
                           void (*)(const std::vector<std::string>&)>&
                  commandMap) {
    commandMap["q"]             = quit_command;
    commandMap["quit"]          = quit_command;
    commandMap["keytest"]       = key_test_command;
}
