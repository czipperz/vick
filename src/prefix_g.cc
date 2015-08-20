#include <map>
#include <ncurses.h>
#include <string>

#include "newmove.hh"
#include "show_message.hh"

static std::map<char,void (*)()> listeners;

inline static void initializeListeners() {
    listeners['g'] = mvsop;
}

void prefix_g() {
    initializeListeners();

    char ch = getch();
    std::map<char,void (*)()>::iterator it = listeners.find(ch);
    if(it == listeners.end()) {
        show_message((std::string("Didn't recognize key press inside `g': ") + ch).c_str());
    } else {
        it->second();
    }
}
