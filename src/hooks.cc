#include <map>
#include <vector>
#include "hooks.hh"

namespace vick {

void hook::proc(contents& contents) {
    for (auto& f : functions) {
        f(contents);
    }
}

void hook::add(void (*f)(contents&)) { functions.push_back(f); }

namespace hooks {
hook save;
hook refresh;
hook mode_enter;
hook open_file;
hook contents_created;
hook contents_deleted;
}

}
