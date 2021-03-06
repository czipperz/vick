/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <ncurses.h>

#include "configuration.hh"
#include "key_aliases.hh"

#include "basic_commands.hh"
#include "command_listeners.hh"
#include "mode.hh"
#include "open_file.hh"
#include "prefix.hh"
#include "prefix_key.hh"
#include "vick-compile/lib.hh"
#include "vick-find/lib.hh"
#include "vick-insert-mode/lib.hh"
#include "vick-join/lib.hh"
#include "vick-linear-change-manager/lib.hh"
#include "vick-move/lib.hh"
#include "vick-open-line/lib.hh"
#include "vick-page/lib.hh"
#include "vick-write-file/lib.hh"

namespace vick {

char QUIT_KEY = CONTROL_G;

move_t TAB_SIZE = 8;

move_t BOTTOM_HEIGHT = 1;

void (*PUSH_BACK_CHANGE)(contents&, std::shared_ptr<change>) =
    vick::linear_change_manager::push_back_change;

// I personally find _ an annoying deliminator as it doesn't split
// variables / tokens in many languages.
std::string DELIMINATORS =
    "!@#$%^&*()-" /*_*/ "=+[]{}\\|;:'\",.<>/?`~";

std::string MATCHES = "()[]{}";

bool use_colors() {
    static const constexpr bool use_colors = true;
    return use_colors and has_colors();
}

void init_conf() { init_pair(1, COLOR_WHITE, COLOR_BLUE); }

void add_listeners() {
    /* global_normal_map binds */ {
        global_normal_map['j'] = move::left_char;
        global_normal_map['k'] = move::forward_line;
        global_normal_map['l'] = move::backward_line;
        global_normal_map[';'] = move::right_char;

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

        global_normal_map['^'] = move::start_text;
        global_normal_map['0'] = move::start_line;
        global_normal_map['$'] = move::end_line;

        global_normal_map['%'] = move::match;

        global_normal_map['|'] = move::column;
        global_normal_map['\\'] = move::line;

        global_normal_map[':'] = command_executor;

        global_normal_map['G'] = move::end_buffer;

        global_normal_map['w'] = move::forward_begin_word;
        global_normal_map['W'] = move::forward_begin_wword;
        global_normal_map['e'] = move::forward_end_word;
        global_normal_map['E'] = move::forward_end_wword;
        global_normal_map['b'] = move::backward_begin_word;
        global_normal_map['B'] = move::backward_begin_wword;

        global_normal_map['f'] = find::move_forward_find_i;
        global_normal_map['F'] = find::move_backward_find_i;
        global_normal_map['t'] = find::move_forward_until_match_i;
        global_normal_map['T'] = find::move_backward_until_match_i;

        global_normal_map['r'] = replace_character;
        global_normal_map['x'] = remove_character;

        global_normal_map['i'] = insert_mode::enter_insert_mode;
        global_normal_map['a'] = insert_mode::enter_append_mode;
        global_normal_map['R'] = insert_mode::enter_replace_mode;

        global_normal_map['o'] = open_line::open_line_below;
        global_normal_map['O'] = open_line::open_line_above;

        global_normal_map['J'] = join::join_two_lines;

        global_normal_map['u'] = linear_change_manager::undo_change;
        global_normal_map[CONTROL_R] =
            linear_change_manager::redo_change;

        global_normal_map['.'] =
            linear_change_manager::reapply_change;

        global_normal_map[CONTROL_B] = page::move_up_page;
        global_normal_map[CONTROL_F] = page::move_down_page;
        global_normal_map[CONTROL_U] = page::move_up_half_page;
        global_normal_map[CONTROL_D] = page::move_down_half_page;

        global_normal_map['q'] = quit_command;
    }

    /* Example config for prefix key */ {
        prefix prefix_g("g");

        // binds inside g (``gg``)
        prefix_g.push_back('g', move::start_buffer);

        // put this last as it copies by value
        global_normal_map['g'] = prefix_g;
    }

    {
        prefix prefix_z("z");
        prefix_z.push_back('t', page::move_to_window_top);
        prefix_z.push_back('m', page::move_to_window_middle);
        prefix_z.push_back('b', page::move_to_window_bottom);

        prefix_z.push_back('T', page::recenter_top);
        prefix_z.push_back('M', page::recenter_middle);
        prefix_z.push_back('B', page::recenter_bottom);

        global_normal_map['z'] = prefix_z;
    }

    {
        prefix alt(std::string(1, ESCAPE));
        alt.push_back('m', move::start_text);

        global_normal_map[ESCAPE] = alt;
    }
}

void add_commands() {
    global_command_map["q"] = quit_command;
    global_command_map["quit"] = quit_command;
    global_command_map["colortest"] = color_test_command;
    global_command_map["o"] = open_file_i;
    global_command_map["open"] = open_file_i;
    global_command_map["w"] = write_file::write;
}
}
