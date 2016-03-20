#include <map>
#include <vector>
#include "hooks.hh"

namespace vick {
namespace hook {

hook_t save = gen();
hook_t refresh = gen();
hook_t mode_enter = gen();
hook_t open_file = gen();
hook_t contents_created = gen();
hook_t contents_deleted = gen();

hook_t gen() {
    static hook_t n = 0;
    return n++;
}

static std::map<hook_t, std::vector<void (*)(contents&)> > hooks;

void proc(hook_t hook, contents& contents) {
    try {
        auto& x = hooks.at(hook);
        for (auto& i : x)
            i(contents);
    } catch (const std::out_of_range&) {
    }
}

void add(hook_t hook, void (*val)(contents&)) {
    hooks[hook].push_back(val);
}
}
}
