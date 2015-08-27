#ifndef HEADER_GUARD_CLASS_CONTENTS_H
#define HEADER_GUARD_CLASS_CONTENTS_H

#include <vector>
#include <string>

#include "change.hh"
#include "mode.hh"

class contents {
    public:
    std::vector<std::string> cont;
    unsigned long
        y,x,desired_x,
        y_offset,
        max_y,max_x;
    bool waiting_for_desired;
    mode& m;
    std::vector<change> changes;

    contents(std::vector<std::string> cont
             = std::vector<std::string>(),
             mode& m = mode::fundamental);
    contents(mode& m);
    contents(long y, long x,
             mode& m = mode::fundamental);

    void push_back(const std::string& str);
};

#endif
