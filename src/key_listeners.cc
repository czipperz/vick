#include <map>
#include <ncurses.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "show_message.hh"
#include "hooks.hh"

static std::map<char,void (*)()> listeners;

void loop() {
    add_listeners(listeners);
    add_hook(Hook::REFRESH,hook_show_message);

    while(true) {
        char ch = getch();
        clear_message();
        std::map<char,void (*)()>::iterator it = listeners.find(ch);
        if(it == listeners.end()) {
            show_message((std::string("Didn't recognize key press: ")
                          + ch).c_str());
        } else {
            clear_message();
            it->second();
        }
    }
}
