#include <map>
#include <string>
#include <vector>

#include "basic_commands.h"
#include "command_listeners.h"
#include "move.h"
#include "prefix_g.h"

int TAB_SIZE() { return 8; }

void mvDD() { mvrel(1,0); }

void add_listeners(std::map<char,void (*)()>& listeners) {
    listeners['j'] = mvl1;
    listeners['k'] = mvd1;
    listeners['d'] = mvDD;
    listeners['l'] = mvu1;
    listeners[';'] = mvr1;

    listeners['^'] = mvsol;
    listeners['0'] = mvsot;
    listeners['$'] = mveol;
    listeners[':'] = command_executor;

    listeners['g'] = prefix_g;
    listeners['G'] = mveop;
    listeners['w'] = mvfw;
    listeners['b'] = mvbw;
}

void add_commands(std::map<std::string,
                           void (*)(const std::vector<std::string>&)>&
                  commandMap) {
    commandMap["q"]     = quit_command;
    commandMap["quit"]  = quit_command;
}
