#include <map>
#include <vector>
#include "hooks.hh"

namespace vick {

hook hook_save = gen_hook();
hook hook_enter_insert_mode = gen_hook();
hook hook_exit_insert_mode = gen_hook();
hook hook_refresh = gen_hook();
hook hook_mode_enter = gen_hook();

hook gen_hook()
{
    static hook n = 0;
    return n++;
}

static std::map<hook, std::vector<void (*)()> > hooks;

void proc_hook(hook hook)
{
    auto& x = hooks[hook];
    for (auto& i : x) i();
}

void add_hook(hook hook, void (*val)())
{
    hooks[hook].push_back(val);
}

}
