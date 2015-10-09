// ensure that configuration variables are exported properly
#include "configuration.hh"

// ensure that the plugins are properly installed, which doesn't happen in testing
#ifndef testing
#  include <functional>
#  include "basic_commands.hh"
#  include "command_listeners.hh"
#  include "mode.hh"
#  include "../plugins/vick-move/src/move.hh"
#  include "../plugins/vick-insert-mode/src/insert_mode.hh"
#  include "prefix.hh"
#  include "prefix_key.hh"
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

        global_normal_map['1'] = prefix_key_1;
        global_normal_map['2'] = prefix_key_2;
        global_normal_map['3'] = prefix_key_3;
        global_normal_map['4'] = prefix_key_4;
        global_normal_map['5'] = prefix_key_5;
        global_normal_map['6'] = prefix_key_6;
        global_normal_map['7'] = prefix_key_7;
        global_normal_map['8'] = prefix_key_8;
        global_normal_map['9'] = prefix_key_9;

        global_normal_map['^'] = mvsol;
        global_normal_map['0'] = mvsot;
        global_normal_map['$'] = mveol;
        global_normal_map[':'] = command_executor;

        global_normal_map['G'] = mveop;
        global_normal_map['w'] = mvfw;
        global_normal_map['W'] = mvfww;
        global_normal_map['e'] = mvfeow;
        global_normal_map['E'] = mvfeoww;
        global_normal_map['b'] = mvbw;
        global_normal_map['B'] = mvbww;

        global_normal_map['r'] = replace_character;

        global_normal_map['i'] = enter_insert_mode;
        global_normal_map['a'] = enter_append_mode;
        global_normal_map['R'] = enter_replace_mode;
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
