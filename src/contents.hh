#ifndef HEADER_GUARD_CLASS_CONTENTS_H
#define HEADER_GUARD_CLASS_CONTENTS_H

#include <vector>
#include <string>

#include "change.hh"
#include "mode.hh"

class contents {
    private:
    const mode* m; // not deleted in destructor

    public:
    std::vector<std::string> cont;
    unsigned long
        y,x,desired_x,
        y_offset,
        max_y,max_x;
    bool waiting_for_desired;
    std::vector<change> changes;

    contents(std::vector<std::string> cont =
             std::vector<std::string>(),
             mode* m = &mode::fundamental);
    contents(mode* m);
    contents(long y, long x,
             mode* m = &mode::fundamental);

    bool operator()(char) const;

    void refreshmaxyx();

    void push_back(const std::string& str);
};

#endif
