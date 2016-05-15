#ifndef HEADER_GUARD_HOOKS_H
#define HEADER_GUARD_HOOKS_H

#include "contents.hh"

namespace vick {

/*!
 * \file hooks.hh
 *
 * \brief Defines how to hook processes in with one another so that
 * one action will always accompany another.
 *
 * `hook.proc(contents&)` will call all the functions added in
 * `hook.add(void (*)(contents&))`
 */

class hook {
public:
    hook() = default;
    ~hook() = default;
    hook(hook&&) = default;

    /*!
     * \brief Calls all the functions associated with this hook.
     *
     * \see add(contents&)
     */
    void proc(contents&);

    /*!
     * \brief Associates the function given with the hook.
     *
     * The function argument is guarenteed to be called whenever
     * `proc()` is called on this hook.
     *
     * There can be multiple functions for a certain hook.  They will
     * be called in the order they were added.
     */
    void add(void (*)(contents&));

private:
    hook(const hook&) = delete;

    std::vector<void (*)(contents&)> functions;
};

namespace hooks {

extern hook save;
extern hook refresh;
extern hook mode_enter;
extern hook open_file;
extern hook contents_created;
extern hook contents_deleted;
}
}

#endif
