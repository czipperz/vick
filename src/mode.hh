#ifndef HEADER_GUARD_MODE_H
#define HEADER_GUARD_MODE_H

#include <functional>
#include <map>
#include <string>

extern std::map < char, std::function<void ()> > global_normal_map;
extern std::map < char, std::function<void ()> > global_insert_map;

struct mode {
    private:
    std::string name;
    // true = has binding
    bool (*handle)(char);


    public:
    mode(const std::string&, bool (*const handle)(char));

    bool operator()(char);

    mode(const mode&);
    mode& operator=(const mode&);

    std::string get_name();

    static mode fundamental; // use global maps only
};
#endif
