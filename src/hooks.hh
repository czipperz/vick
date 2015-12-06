#ifndef HEADER_GUARD_HOOKS_H
#define HEADER_GUARD_HOOKS_H

#include "contents.hh"

namespace vick {

/*!
 * \file hooks.hh
 *
 * \brief Defines how to hook processes in with one another so that one
 *        action will always accompany another.
 *
 * proc_hook(hook) will call all the functions added in add_hook(hook,
 *void(*)())
 *
 */

/*!
 * \brief Distinguishes normal <code>unsigned int</code>s from being confused as
 * hooks.
 */
using hook_t = unsigned int;

namespace hook {

extern hook_t save;
extern hook_t refresh;
extern hook_t mode_enter;
extern hook_t contents_created;
extern hook_t contents_deleted;

/*!
 * \brief Generates a unique hook id
 *
 * This id is made at runtime and is <i>not</i> thread safe.
 */
hook_t gen();
/*!
 * \brief Calls all the functions associated to the hook given
 *
 * To associate a function with a hook use add_hook()
 */
void proc(hook_t, contents&);
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
void add(hook_t, void (*)(contents&));

}
}

#endif
