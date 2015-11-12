#include <ncurses.h>

// ensure that configuration variables are exported properly
#include "configuration.hh"
#include "key_aliases.hh"

// ensure that the plugins are properly installed, which doesn't happen in
// testing
#ifndef testing
#  include "basic_commands.hh"
#  include "command_listeners.hh"
#  include "mode.hh"
#  include "../plugins/vick-move/src/move.hh"
#  include "../plugins/vick-insert-mode/src/insert_mode.hh"
#  include "../plugins/vick-open-line/src/open_line.hh"
#  include "../plugins/vick-join/src/join.hh"
#  include "../plugins/vick-find/src/find.hh"
#  include "../plugins/vick-linear-change-manager/src/linear-change-manager.hh"
#  include "prefix.hh"
#  include "prefix_key.hh"
#endif

namespace vick {

char QUIT_KEY = _control_g;

int TAB_SIZE = 8;

void (*PUSH_BACK_CHANGE)(contents&, std::shared_ptr<change>) =
// ensure that the plugins are properly installed, which doesn't
// happen in testing
#ifndef testing
    vick::linear_change_manager::push_back_change
#else
// if plugins not installed than do nothing
    [](contents&, std::shared_ptr<change>) {}
#endif
    ;

std::string DELIMINATORS = "!@#$%^&*()-_=+[]{}\\|;:'\",.<>/?`~";

bool use_colors()
{
    static const constexpr bool use_colors = true;
    return use_colors && has_colors();
}

void init_conf()
{
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
}

void add_listeners()
{
// ensure that the plugins are properly installed, which doesn't happen in
// testing
#ifndef testing
    /* global_normal_map binds */ {
        global_normal_map['j'] = move::mvb;
        global_normal_map['k'] = move::mvd;
        global_normal_map['l'] = move::mvu;
        global_normal_map[';'] = move::mvf;

        global_normal_map['1'] = prefix_key_1;
        global_normal_map['2'] = prefix_key_2;
        global_normal_map['3'] = prefix_key_3;
        global_normal_map['4'] = prefix_key_4;
        global_normal_map['5'] = prefix_key_5;
        global_normal_map['6'] = prefix_key_6;
        global_normal_map['7'] = prefix_key_7;
        global_normal_map['8'] = prefix_key_8;
        global_normal_map['9'] = prefix_key_9;
        prefix_key_times_ten = '0';

        global_normal_map['^'] = move::mvsol;
        global_normal_map['0'] = move::mvsot;
        global_normal_map['$'] = move::mveol;

        global_normal_map['|'] = move::mvcol;
        global_normal_map['\\'] = move::mvline;

        global_normal_map[':'] = command_executor;

        global_normal_map['G'] = move::mveop;

        global_normal_map['w'] = move::mvfw;
        global_normal_map['W'] = move::mvfww;
        global_normal_map['e'] = move::mvfeow;
        global_normal_map['E'] = move::mvfeoww;
        global_normal_map['b'] = move::mvbw;
        global_normal_map['B'] = move::mvbww;

        global_normal_map['f'] = find::move_forward_find_i;
        global_normal_map['F'] = find::move_backward_find_i;
        global_normal_map['t'] = find::move_forward_until_match_i;
        global_normal_map['T'] = find::move_backward_until_match_i;

        global_normal_map['r'] = replace_character;

        global_normal_map['i'] = insert_mode::enter_insert_mode;
        global_normal_map['a'] = insert_mode::enter_append_mode;
        global_normal_map['R'] = insert_mode::enter_replace_mode;

        global_normal_map['o'] = open_line::open_line_below;
        global_normal_map['O'] = open_line::open_line_above;

        global_normal_map['J'] = join::join_two_lines;

        global_normal_map['u'] = linear_change_manager::undo_change;
        global_normal_map[_control_r] = linear_change_manager::redo_change;

        global_normal_map['.'] = linear_change_manager::reapply_change;
    }

    /* Example config for prefix key */ {
        prefix prefix_g("g");

        // binds inside g (``gg``)
        prefix_g.push_back('g', move::mvsop);

        // put this last as it copies by value
        global_normal_map['g'] = prefix_g;
    }
#endif
}

void add_commands(std::map<
    std::string, std::function<boost::optional<std::shared_ptr<change> >(
                     contents&, boost::optional<int>)> >& commandMap)
{
// ensure that the plugins are properly installed, which doesn't happen in
// testing
#ifndef testing
    commandMap["q"] = quit_command;
    commandMap["quit"] = quit_command;
    commandMap["keytest"] = key_test_command;
    commandMap["colortest"] = color_test_command;
#endif
}

}
