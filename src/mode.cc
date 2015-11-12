#include <functional>
#include <boost/optional.hpp>

#include "configuration.hh"
#include "key_aliases.hh"
#include "file_contents.hh"
#include "mode.hh"
#include "show_message.hh"

namespace vick {

std::map < char, std::function < boost::optional< std::shared_ptr<change> >
                                     (contents&, boost::optional<int>) > >
    global_normal_map,
    global_insert_map;

mode::mode(const std::string& name, bool (*handle)(char))
    : name(name)
    , handle(handle) {
    static int uid = 0;
    unique_id = uid++;
}

bool mode::operator()(char ch) const {
    return handle(ch);
}

const std::string& mode::get_name() const {
    return name;
}

bool mode::operator==(const mode& other) const {
    return unique_id == other.unique_id;
}
bool mode::operator!=(const mode& other) const {
    return unique_id != other.unique_id;
}

static bool fundamental_handle(char ch) {
    if(ch == _resize) return true;

    auto it = global_normal_map.find(ch);
    if(it == global_normal_map.end()) return false;

    clear_message();
    auto optional = it->second(get_contents(),boost::none);
    if(optional) PUSH_BACK_CHANGE(get_contents(), *optional);
    return true;
}

mode fundamental_mode("Fundamental", fundamental_handle);

}
