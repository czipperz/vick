#ifndef HEADER_GUARD_PREFIX_H
#define HEADER_GUARD_PREFIX_H

#include <map>
#include <functional>

class prefix {
    private:
    // use this for documentation
    char prech;

    std::map < char, std::function<void ()> > map;

    public:
    prefix(char);
    void push_back(char, std::function<void ()>);
    void push_back(char, void (*)());
    void operator()();
};
void setup_prefix_g();
void prefix_g();

#endif
