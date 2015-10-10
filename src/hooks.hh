#ifndef HEADER_GUARD_HOOKS_H
#define HEADER_GUARD_HOOKS_H


using hook = unsigned int;

extern hook hook_move;
extern hook hook_save;
extern hook hook_edit;
extern hook hook_refresh;
extern hook hook_mode_enter;

hook gen_hook();
void proc_hook(hook);
void add_hook (hook, void (*)());

#endif
