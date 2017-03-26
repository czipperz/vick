/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_CHANGE_H
#define HEADER_GUARD_CHANGE_H

#include <boost/optional.hpp>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace vick {

class contents;

/*!
 * \file change.hh
 *
 * \brief Defines the change class, representing a change from one
 * `contents` to another.
 */

/*!
 * \class change change.hh "change.hh"
 * \brief Represents a change from one `contents` to another
 *
 * It allows for virtual dispath on undoing, redoing, and regeneration
 * of a textual edit to the buffer.  `undo` will put the contents in
 * the state it was before the edit.  `redo` will put the contents in
 * the state it was after the edit.  `regenerate` generates a new
 * change at the new position in the buffer, or acting on the new
 * buffer state that must be manually `redo`ne on the contents.
 *
 * \see contents
 */
struct change {
    change() = default;

    virtual ~change() = default;

    /*!
     * \brief Return true if the edit changes `contents::cont`.
     */
    virtual bool is_overriding() const noexcept = 0;

    /*!
     * \brief Undoes this edit
     */
    virtual void undo(contents&) = 0;

    /*!
     * \brief Performs this edit again (Use after an undo)
     */
    virtual void redo(contents&) = 0;

    /*!
     * \brief Generates a change that will act over the new contents
     */
    virtual std::shared_ptr<change>
    regenerate(const contents&) const = 0;

    /*!
     * \brief Calls regenerate and then calls redo on the result and
     * returns the regenerated change.
     */
    std::shared_ptr<change> regenerate_and_apply(contents& cont);

private:
    change(const change&) = delete;
    change& operator=(const change&) = delete;
};

struct combination_change : change {
    combination_change() = default;
    combination_change(std::initializer_list<std::shared_ptr<change> >);
    void add_change(std::shared_ptr<change>);

    ~combination_change() override = default;

    /*!
     * \brief Return true if the edit changes `contents::cont`.
     */
    bool is_overriding() const noexcept override;

    /*!
     * \brief Undoes this edit
     */
    void undo(contents&) override;

    /*!
     * \brief Performs this edit again (Use after an undo)
     */
    void redo(contents&) override;

    /*!
     * \brief Generates a change that will act over the new contents
     */
    std::shared_ptr<change>
    regenerate(const contents&) const override;

    combination_change(const combination_change& other);
    combination_change(combination_change&& other);
    combination_change& operator=(const combination_change& other);
    combination_change& operator=(combination_change&& other);

private:
    std::vector<std::shared_ptr<change> > changes;
};

struct insertion_change : change {
    insertion_change(std::size_t y, std::size_t x, const std::string& str);
    insertion_change(std::size_t y, std::size_t x, std::string&& str);

    ~insertion_change() override = default;

    bool is_overriding() const noexcept override;
    virtual void undo(contents&) override;
    virtual void redo(contents&) override;
    virtual std::shared_ptr<change>
    regenerate(const contents&) const override;

    insertion_change(const insertion_change& other);
    insertion_change(insertion_change&& other);
    insertion_change& operator=(const insertion_change& other);
    insertion_change& operator=(insertion_change&& other);

private:
    std::size_t y, x;
    std::string str;

    friend struct removal_change;
};

struct removal_change : insertion_change {
    removal_change(std::size_t y, std::size_t x, const std::string& str);
    removal_change(std::size_t y, std::size_t x, std::string&& str);

    bool is_overriding() const noexcept override;
    void undo(contents&) override;
    void redo(contents&) override;
    std::shared_ptr<change>
    regenerate(const contents&) const override;
};

}

#include "contents.hh"

namespace vick {
struct full_change : change {
    full_change(const contents& o, const contents& n)
        : o(o)
        , n(n) {}
    full_change(contents&& o, const contents& n)
        : o(std::move(o))
        , n(n) {}
    full_change(const contents& o, contents&& n)
        : o(o)
        , n(std::move(n)) {}
    full_change(contents&& o, contents&& n)
        : o(std::move(o))
        , n(std::move(n)) {}

    ~full_change() = default;

    bool is_overriding() const noexcept override { return true; }
    void undo(contents& cont) override { cont = o; }
    void redo(contents& cont) override { cont = n; }
    std::shared_ptr<change>
    regenerate(const contents& cont) const override {
        return std::make_shared<full_change>(cont, n);
    }

private:
    contents o, n;
};
}

#endif
