/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <algorithm>

#include "split.hh"

namespace vick {

std::vector<std::string> split(const std::string& str, char delim) {
    if (str.empty())
        return {};
    std::vector<std::string> res;
    size_t fir = 0, itr = 0;
    while ((itr = str.find(delim, itr)) != std::string::npos) {
        res.push_back(str.substr(fir, itr - fir));
        fir = ++itr;
    }
    res.push_back(str.substr(fir, itr - fir));
    return res;
}
}
