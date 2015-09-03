#include <functional>
#include <boost/optional.hpp>

#include "file_contents.hh"
#include "contents.hh"
#include "mode.hh"
#include "show_message.hh"

typedef std::function<void (contents&, boost::optional<int>)> fun;

std::map < char, fun > global_normal_map;
std::map < char, fun > global_insert_map;

mode::mode(const std::string& name, bool (*const handle)(char))
    : name(name)
    , handle(handle) { }

bool mode::operator()(char ch) {
    return handle(ch);
}

mode::mode(const mode& other)
    : name(other.name)
    , handle(other.handle) { }

mode& mode::operator=(const mode& other) {
    this->name = other.name;
    this->handle = other.handle;
    return *this;
}

static bool fundamental_handle(char ch) {
    std::map < char, fun > :: iterator
        it = global_normal_map.find(ch);
    if(it == global_normal_map.end()) return false;

    clear_message();
    it->second(*get_contents(),boost::none);
    return true;
}

mode mode::fundamental("Fundamental",fundamental_handle);
