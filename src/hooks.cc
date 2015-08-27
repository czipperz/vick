#include <map>
#include <vector>
#include "hooks.hh"

static std::map<Hook::Hook, std::vector<void (*)()> > hooks;

void proc_hook(Hook::Hook hook) {
    auto& x(hooks[hook]);
    for(auto& i : x) i();
}

void add_hook(Hook::Hook hook, void (*val)()) {
    hooks[hook].push_back(val);
}
