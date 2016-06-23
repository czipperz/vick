/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_CONCAT_C_H
#define HEADER_GUARD_CONCAT_C_H

#include <vector>
#include "change.hh"

namespace vick {

/*!
 * \file concat_c.hh
 * \brief Defines `concat_c`, a simple way to correctly concatenate
 * changes.
 */

/*!
 * \brief Concatenates changes and correctly implements them in order.
 */
struct concat_c : public change {
    /*!
     * \brief Constructs the concat_c as the `concatenation` of the
     * given `changes`.
     */
    concat_c(std::vector<std::shared_ptr<change> > changes)
        : changes(std::move(changes)) {}

    /*!
     * \brief True if any of the changes are considered overriding.
     */
    virtual bool is_overriding() const noexcept override {
        for (std::shared_ptr<change> pt : changes) {
            if (pt->is_overriding())
                return true;
        }
        return false;
    }

    /*!
     * \brief Undoes each change in reverse.
     */
    virtual void undo(contents& contents) override {
        for (auto begin = changes.rbegin(); begin != changes.rend();
             ++begin)
            (*begin)->undo(contents);
    }

    /*!
     * \brief Redoes each change in order.
     */
    virtual void redo(contents& contents) override {
        for (auto begin = changes.begin(); begin != changes.end();
             ++begin)
            (*begin)->redo(contents);
    }

    /*!
     * \brief Regenerate each change in order.
     */
    virtual std::shared_ptr<change>
    regenerate(const contents& contents) const override {
        std::vector<std::shared_ptr<change> > n;
        for (auto pt : changes)
            n.push_back(pt->regenerate(contents));
        return std::make_shared<concat_c>(n);
    }

private:
    std::vector<std::shared_ptr<change> > changes;
};
}

#endif
