#include <string>

#include "configuration.hh"

namespace vick {

int from_visual(const std::string& cont, int x) {
    if (cont.empty())
        return 0;
    int count = 0, til = 0;
    int numTab = 0;
    for (size_t i = 0; i < cont.length(); i++) {
        size_t len;
        if (cont[i] == '\t') {
            len = TAB_SIZE - 1 - til;
            til = 0;
            numTab++;
        } else {
            len = 1;
            til++;
            til %= TAB_SIZE;
        }
        count += len;
        if (count > x - numTab)
            return i;
    }
    return -1;
}

int to_visual(const std::string& cont, int x) {
    int til = 0, xx = -1;
    for (std::string::const_iterator i = cont.begin();
         i <= cont.begin() + x; ++i) {
        if (*i == '\t') {
            xx += TAB_SIZE - til;
            til = 0;
        } else {
            til++;
            til %= TAB_SIZE;
            xx++;
        }
    }
    return xx;
}
}
