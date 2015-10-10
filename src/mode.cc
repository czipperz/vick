#include <functional>
#include <boost/optional.hpp>

#include "key_aliases.hh"
#include "file_contents.hh"
#include "mode.hh"
#include "show_message.hh"

std::map < char, std::function < void (contents&, boost::optional<int>) > >
    global_normal_map,
    global_insert_map;

mode::mode(const std::string& name, bool (*const handle)(char))
    : name(name)
    , handle(handle) { }

bool mode::operator()(char ch) const {
    return handle(ch);
}

const std::string& mode::get_name() const {
    return this->name;
}

static bool fundamental_handle(char ch) {
    if(ch == _resize) return true;

    auto it = global_normal_map.find(ch);
    if(it == global_normal_map.end()) return false;

    clear_message();
    it->second(get_contents(),boost::none);
    return true;
}

mode mode::fundamental("Fundamental",fundamental_handle);
