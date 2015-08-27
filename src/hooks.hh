#ifndef HEADER_GUARD_HOOKS_H
#define HEADER_GUARD_HOOKS_H

namespace Hook {
    enum Hook {
        MOVE,
        SAVE,
        EDIT,
        REFRESH,
        MODE_ENTER,
    };
}

void proc_hook(Hook::Hook);
void add_hook (Hook::Hook, void (*)());

#endif
