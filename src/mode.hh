#ifndef HEADER_GUARD_MODE_H
#define HEADER_GUARD_MODE_H

#include <functional>
#include <map>
#include <string>
#include <boost/optional.hpp>

class contents;

extern std::map < char, std::function < void (contents&, boost::optional<int>) > >
    global_normal_map,
    global_insert_map;

class mode {
    private:
    std::string name;
    // true = has binding
    bool (*handle)(char);


    public:
    mode(const std::string&, bool (*const handle)(char));

    bool operator()(char) const;

    const std::string& get_name() const;

    static mode fundamental; // use global maps only
};
#endif
