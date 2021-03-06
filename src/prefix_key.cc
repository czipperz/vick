/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <ncurses.h>

#include "prefix_key.hh"
#include "show_message.hh"

namespace vick {

char prefix_key_times_ten;

static std::shared_ptr<change>
handle(contents& contents, boost::optional<int> op, int n) {
    int total = n + (op ? op.get() : 0) * 10;
    show_message(std::to_string(total) + "-");
    char c = getch();
    while (c == prefix_key_times_ten) {
        total *= 10;
        show_message(std::to_string(total) + "-");
        c = getch();
    }
    auto x = global_normal_map.find(c);
    if (x == global_normal_map.end()) {
        show_message(std::string("Unbound key: ") +
                     std::to_string(c));
        return nullptr;
    } else {
        showing_message = false;
        return x->second(contents, total);
    }
}

std::shared_ptr<change>
prefix_key_1(contents& contents, boost::optional<int> op) {
    return handle(contents, op, 1);
}
std::shared_ptr<change>
prefix_key_2(contents& contents, boost::optional<int> op) {
    return handle(contents, op, 2);
}
std::shared_ptr<change>
prefix_key_3(contents& contents, boost::optional<int> op) {
    return handle(contents, op, 3);
}
std::shared_ptr<change>
prefix_key_4(contents& contents, boost::optional<int> op) {
    return handle(contents, op, 4);
}
std::shared_ptr<change>
prefix_key_5(contents& contents, boost::optional<int> op) {
    return handle(contents, op, 5);
}
std::shared_ptr<change>
prefix_key_6(contents& contents, boost::optional<int> op) {
    return handle(contents, op, 6);
}
std::shared_ptr<change>
prefix_key_7(contents& contents, boost::optional<int> op) {
    return handle(contents, op, 7);
}
std::shared_ptr<change>
prefix_key_8(contents& contents, boost::optional<int> op) {
    return handle(contents, op, 8);
}
std::shared_ptr<change>
prefix_key_9(contents& contents, boost::optional<int> op) {
    return handle(contents, op, 9);
}
}
