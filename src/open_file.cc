/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <ncurses.h>
#include <fstream>

#include "hooks.hh"
#include "open_file.hh"
#include "prompt.hh"
#include "full_c.hh"

namespace vick {

std::shared_ptr<change>
open_file_i(contents& cont, boost::optional<int>) {
    attron(COLOR_PAIR(1));
    auto opt = prompt("File to open: ");
    attroff(COLOR_PAIR(1));
    if (not opt)
        return nullptr;
    return open_file(cont, *opt);
}

contents open_file(std::string file) {
    contents cont;
    bool& windows = cont.windows_file_endings;
    bool asked = false;

    std::string line;
    std::ifstream myfile(file);

    if (std::getline(myfile, line)) {
        if (not line.empty() and line.back() == '\r') {
            line.pop_back();
            windows = true;
        }
        cont.cont.push_back(line);
        while (std::getline(myfile, line)) {
            if (not line.empty() and line.back() == '\r') {
                if (not windows and not asked) {
                    asked = true;
                    windows =
                        repeat_remove_optional(prompt_yes_no,
                                               "Windows file endings "
                                               "detected, "
                                               "use them when "
                                               "saving? ");
                }
                line.pop_back();
            }
            cont.cont.push_back(line);
        }
    } else {
        cont.cont.push_back("");
    }

    hooks::open_file.proc(cont);

    return cont;
}

std::shared_ptr<change>
open_file(contents& cont, std::string file) {
    contents before = cont;
    cont.y = 0;
    cont.x = 0;
    cont.cont.clear();
    bool& windows = cont.windows_file_endings;
    bool asked = false;
    std::string line;
    std::ifstream myfile(file);

    if (std::getline(myfile, line)) {
        if (not line.empty() and line.back() == '\r') {
            line.pop_back();
            windows = true;
        }
        cont.cont.push_back(line);
        while (std::getline(myfile, line)) {
            if (not line.empty() and line.back() == '\r') {
                if (not windows and not asked) {
                    asked = true;
                    windows =
                        repeat_remove_optional(prompt_yes_no,
                                               "Windows file endings "
                                               "detected, "
                                               "use them when "
                                               "saving? ");
                }
                line.pop_back();
            }
            cont.cont.push_back(line);
        }
    } else
        cont.cont.push_back("");

    hooks::open_file.proc(cont);

    if (before.cont == cont.cont)
        return nullptr;
    return std::make_shared<full_c>(std::move(before), cont);
}
}
