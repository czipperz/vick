#include <map>
#include <ncurses.h>
#include <string>

#include "mode.hh"
#include "show_message.hh"
#include "prefix.hh"

prefix::prefix(char ch)
    : prech(ch) { }

void prefix::push_back(char ch, std::function<void ()> fun) {
    this->map[ch] = fun;
}

void prefix::push_back(char ch, void (*fun)()) {
    this->map[ch] = std::function<void ()>(fun);
}

void prefix::operator()() {
    char ch = getch();
    auto it = map.find(ch);
    if(it == map.end()) {
        show_message((std::string("Didn't recognize key press inside"
                                  "prefix key '") + prech + '\'')
                     .c_str());
    } else {
        it->second();
    }
}
