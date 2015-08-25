#include <map>
#include <vector>
#include "hooks.hh"

static std::map<Hook::Hook, std::vector<void (*)()> > hooks;
static bool init(false);
static void tryinit() {
    if(!init) {
        hooks[Hook::MOVE] = std::vector<void (*)()>();
        hooks[Hook::SAVE] = std::vector<void (*)()>();
        hooks[Hook::EDIT] = std::vector<void (*)()>();
    }
}

void proc_hook(Hook::Hook hook) {
    tryinit();
    std::vector<void (*)()> x = hooks[hook];
    for(int i = 0; i < x.size(); i++)
        x[i]();
}

void add_hook(Hook::Hook hook, void (*val)()) {
    tryinit();
    hooks[hook].push_back(val);
}
