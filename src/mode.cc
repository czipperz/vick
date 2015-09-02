#include <functional>

#include "mode.hh"
#include "show_message.hh"

std::map < char, std::function<void ()> > global_normal_map;
std::map < char, std::function<void ()> > global_insert_map;

static bool fundamental_handle(char);
static bool programming_handle(char);
static bool text_handle(char);

mode mode::fundamental("Fundamental",fundamental_handle);
mode mode::text       ("Text mode"  ,text_handle);
mode mode::programming("Programming",programming_handle);

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
    auto it = global_normal_map.find(ch);
    if(it == global_normal_map.end()) return false;

    clear_message();
    it->second();
    return true;
}
static bool programming_handle(char ch) {
    if(fundamental_handle(ch)) return true;
    return true;
}
static bool text_handle(char ch) {
    if(fundamental_handle(ch)) return true;
    return true;
}
