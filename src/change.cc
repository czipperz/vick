#include "change.hh"

namespace vick {

std::shared_ptr<change> change::regenerate_and_apply(contents& cont) {
    auto x = regenerate(cont);
    x->redo(cont);
    return x;
}

}
