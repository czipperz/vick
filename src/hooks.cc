#include <map>
#include <vector>
#include "hooks.hh"

static std::map<Hook::Hook, std::vector<void (*)()> > hooks;

void proc_hook(Hook::Hook hook) {
    std::vector<void (*)()> x = hooks[hook];
    for(int i = 0; i < x.size(); i++)
        x[i]();
}

void add_hook(Hook::Hook hook, void (*val)()) {
    hooks[hook].push_back(val);
}
