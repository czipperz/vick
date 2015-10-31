#include <ncurses.h>

#include "contents.hh"
#include "show_message.hh"

void contents::push_back(std::shared_ptr<change> change)
{
    if (changes_i == 0)
        _changes.clear();
    else if (_changes.size() > changes_i)
        _changes.erase(_changes.begin() + changes_i, _changes.end());
    _changes.push_back(change);
    _changes_i = _changes.size();
}

boost::optional<std::shared_ptr<change> > undo_change(contents& contents,
                                                      boost::optional<int>)
{
    if (contents.changes.size() == 0 || contents.changes_i == 0) {
        show_message("No changes to undo");
        return boost::none;
    }
    contents.changes[--contents._changes_i]->undo(contents);
    return boost::none;
}

boost::optional<std::shared_ptr<change> > redo_change(contents& contents,
                                                      boost::optional<int>)
{
    if (contents.changes.size() == 0 || contents.changes_i >= contents.changes.size()) {
        show_message("No changes to redo");
        return boost::none;
    }
    contents.changes[contents._changes_i++]->redo(contents);
    return boost::none;
}

boost::optional<std::shared_ptr<change> > reapply_change(contents& contents,
                                                         boost::optional<int>)
{
    if (contents.changes.size() == 0) {
        show_message("No changes to reapply");
        return boost::none;
    }
    contents._changes_i++;
    auto x = contents.changes.back()->regenerate(contents);
    x->redo(contents);
    return x;
}
