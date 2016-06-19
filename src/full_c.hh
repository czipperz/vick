#ifndef HEADER_GUARD_FULL_C_H
#define HEADER_GUARD_FULL_C_H

#include "contents.hh"

namespace vick {
struct full_c : public change {
    full_c(contents o, contents n)
        : o(std::move(o))
        , n(std::move(n)) {}
    virtual bool is_overriding() const noexcept override {
        return true;
    }
    virtual void undo(contents& cont) override { cont = o; }
    virtual void redo(contents& cont) override { cont = n; }
    virtual std::shared_ptr<change>
    regenerate(const contents& cont) const override {
        return std::make_shared<full_c>(cont, n);
    }
private:
    contents o, n;
};
}

#endif
