/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "split.hh"

namespace vick {

std::vector<std::string>
split(const std::string& str, char delim) {
    if (str.empty())
        return {};
    std::vector<std::string> res;
    size_t fir = 0, itr = 0;
    while ((itr = str.find(delim, itr)) != std::string::npos) {
        res.push_back(str.substr(fir, itr - fir));
        fir = ++itr;
    }
    res.push_back(str.substr(fir));
    return res;
}

std::vector<std::string>
split_by_line(const std::string& str) {
    if (str.empty())
        return {};
    std::vector<std::string> res;
    // Use `c_str()` so `*end == 0` instead of undefined behavior.
    // This makes it safe to access the next character without bounds
    // checking.
    auto i = str.c_str(), backup = i;
    const auto e = i + str.size();
    for (; i != e; ++i) {
        // windows
        if (*i == '\r' && i[1] == '\n') {
            res.push_back({backup, i});
            // skip both (loop does another increment)
            ++i;
            backup = i + 1;
        } else if (*i == '\n') {
            res.push_back({backup, i});
            backup = i + 1;
        }
    }
    res.push_back({backup, e});
    return res;
}
}
