#include <map>
#include <ncurses.h>
#include <string>

#include "mode.hh"
#include "show_message.hh"
#include "prefix.hh"

prefix::prefix(char ch)
    : prech(ch) { }

void prefix::push_back(char ch, std::function<void(contents&, boost::optional<int>)> fun) {
    this->map[ch] = fun;
}
void prefix::push_back(char ch, void (*fun)(contents&, boost::optional<int>)) {
    this->map[ch] = std::function<void(contents&, boost::optional<int>)>(fun);
}

void prefix::operator()(contents& cont, boost::optional<int> op) {
    char ch = getch();
    auto it = map.find(ch);
    if(it == map.end()) {
        show_message((std::string("Didn't recognize key press inside"
                                  "prefix key '") + prech + '\'')
                     .c_str());
    } else {
        it->second(cont, op);
    }
}
