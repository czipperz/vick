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
#include "to_str.hh"

void loop() {
    add_listeners();
    add_hook(Hook::REFRESH,hook_show_message);

    while(true) {
        char ch = getch();
        clear_message();
        if(!get_contents()->m(ch)) {
            show_message((std::string("Didn't recognize key press: ")
                          + ch).c_str());
        } else {
            show_message((std::string("x,y: (")
                          + int_to_str(get_contents()->x) + ','
                          + int_to_str(get_contents()->y) + ')').c_str());
        }
        get_contents()->refreshmaxyx();
        print_contents(get_contents());
    }
}
