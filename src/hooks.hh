#ifndef HEADER_GUARD_HOOKS_H
#define HEADER_GUARD_HOOKS_H

/*!
 * \file hooks.hh
 *
 * \brief Defines how to hook processes in with one another so that one
 *        action will always accompany another.
 *
 * proc_hook(hook) will call all the functions added in add_hook(hook, void(*)())
 *
 */

/*!
 * \brief Distinguishes normal <code>unsigned int</code>s from being confused as hooks.
 */
using hook = unsigned int;

extern hook hook_save;
extern hook hook_enter_insert_mode;
extern hook hook_exit_insert_mode;
extern hook hook_refresh;
extern hook hook_mode_enter;

/*!
 * \brief Generates a unique hook id
 *
 * This id is made at runtime and is <i>not</i> thread safe.
 */
hook gen_hook();
/*!
 * \brief Calls all the functions associated to the hook given
 *
 * To associate a function with a hook use add_hook()
 */
void proc_hook(hook);
/*!
 * \brief Associates the function given with a hook
 *
 * The function argumen is guarenteed to be called whenever
 * proc_hook() is called with the same hook as this method is called
 * with.
 *
 * There can be multiple functions for a certain hook.  They will be
 * called in the order they were added with add_hook()
 */
void add_hook (hook, void (*)());

#endif
