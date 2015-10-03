// ensure that configuration variables are exported properly
#include "configuration.hh"

// ensure that the plugins are properly installed, which doesn't happen in testing
#ifndef testing
#  include <functional>
#  include "basic_commands.hh"
#  include "command_listeners.hh"
#  include "mode.hh"
#  include "move.hh"
#  include "prefix.hh"
#endif

const int TAB_SIZE = 8;

const std::string DELIMINATORS = "!@#$%^&*()-_=+[]{}\\|;:'\",.<>/?`~";

void add_listeners() {
// ensure that the plugins are properly installed, which doesn't happen in testing
#ifndef testing
    /* global_normal_map binds */ {
        global_normal_map['j'] = mvb;
        global_normal_map['k'] = mvd;
        global_normal_map['l'] = mvu;
        global_normal_map[';'] = mvf;

        global_normal_map['^'] = mvsol;
        global_normal_map['0'] = mvsot;
        global_normal_map['$'] = mveol;
        global_normal_map[':'] = command_executor;

        global_normal_map['G'] = mveop;
        global_normal_map['w'] = mvfw;
        global_normal_map['e'] = mvfeow;
        global_normal_map['b'] = mvbw;
    }

    /* Example config for prefix key */ {
        prefix prefix_g('g');

        // binds inside g (``gg``)
        prefix_g.push_back('g',mvsop);

        // put this last as it copies by value
        global_normal_map['g'] = prefix_g;
    }
#endif
}

void add_commands(std::map<std::string,
                           std::function<void(contents&, boost::optional<int>)> >&
                  commandMap) {
// ensure that the plugins are properly installed, which doesn't happen in testing
#ifndef testing
    commandMap["q"]             = quit_command;
    commandMap["quit"]          = quit_command;
    commandMap["keytest"]       = key_test_command;
#endif
}
