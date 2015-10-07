#ifndef HEADER_GUARD_CLASS_CONTENTS_H
#define HEADER_GUARD_CLASS_CONTENTS_H

#include <vector>
#include <string>

#include "change.hh"
#include "mode.hh"

class contents {
    private:
    const mode* m;

    public:
    std::vector<std::string> cont;
    unsigned long
        y = 0, x = 0, desired_x = 0,
        y_offset = 0,
        max_y,max_x;
    bool waiting_for_desired = false,
         refresh = true,
         delete_mode = false,
         is_inserting = false;
    std::vector<change> changes;

    contents(std::vector<std::string> cont =
             std::vector<std::string>(),
             mode* m = &mode::fundamental);
    contents(mode* m);
    contents(long y, long x,
             mode* m = &mode::fundamental);

    bool operator()(char) const;

    ~contents();
    contents(const contents&);
    contents(contents&&);
    contents& operator=(const contents&);
    contents& operator=(contents&&);

    void refreshmaxyx();

    void push_back(const std::string& str);
};

#endif
