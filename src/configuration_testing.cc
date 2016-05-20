/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "configuration.hh"

namespace vick {

char QUIT_KEY = 0;
move_t TAB_SIZE = 1;
void (*PUSH_BACK_CHANGE)(contents&,
                         std::shared_ptr<change>) = nullptr;
std::string DELIMINATORS = "!@#$%^&*()-=+[]{}\\|;:'\",.<>/?`~";
std::string MATCHES = "()[]{}";

bool use_colors() { return true; }
void init_conf() {}
void add_listeners() {}
void add_commands(
    std::map<std::string,
             std::function<boost::optional<std::shared_ptr<change> >(
                 contents&, boost::optional<int>)> >&) {}
}
