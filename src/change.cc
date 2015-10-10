#include "change.hh"

change::change(std::function<void(contents&)> redo,
               std::function<void(contents&)> undo)
    : _redo(redo)
    , _undo(undo) { }

change change::operator>>(const change& other) const {
    std::function<void(contents&)> redo(
        [&, other, this](contents& contents) {
            other.redo(contents);
            this->redo(contents);
        });
    std::function<void(contents&)> undo(
        [&, other, this](contents& contents) {
            other.undo(contents);
            this->undo(contents);
        });
    return change(redo, undo);
}

void change::redo(contents& contents) const {
    _redo(contents);
}

void change::undo(contents& contents) const {
    _undo(contents);
}
