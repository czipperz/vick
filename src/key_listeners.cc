#include <map>
#include <ncurses.h>
#include <string>
#include <typeinfo>
#include <vector>

#include "configuration.hh"
#include "file_contents.hh"
#include "key_listeners.hh"
#include "show_message.hh"
#include "hooks.hh"

void loop() {
    add_listeners();
    add_hook(Hook::REFRESH,hook_show_message);

    while(true) {
        char ch(getch());
        clear_message();
        if(!get_contents()->m(ch)) {
            show_message((std::string("Didn't recognize key press: ")
                          + ch).c_str());
        }
    }
}
