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
        bool b = !get_contents()(ch);
        get_contents().refreshmaxyx();
        if(get_contents().refresh) print_contents(get_contents());
        if(b) {
            show_message((std::string("Didn't recognize key press: ")
                          + ch).c_str());
        } else {
            int vis_y,vis_x;
            getyx(stdscr,vis_y,vis_x);
            show_message((std::string("y,x,vis_y,vis_x: (")
                          + int_to_str(get_contents().y) + ','
                          + int_to_str(get_contents().x) + ','
                          + int_to_str(vis_y) + ','
                          + int_to_str(vis_x) + ')').c_str());
        }
    }
}
