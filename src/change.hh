#ifndef HEADER_GUARD_CHANGE_H
#define HEADER_GUARD_CHANGE_H

#include <functional>
#include <string>
#include <vector>

class contents;

class change {
    private:
    std::function<void(contents&)> _redo, _undo;

    public:
    change(std::function<void(contents&)> redo, std::function<void(contents&)> undo);

    //combines two changes together
    //mvd >> mvsot >> mvf   would past the first character on the next line
    change operator>>(const change&) const;

    void redo(contents&) const;
    void undo(contents&) const;
};

#endif
