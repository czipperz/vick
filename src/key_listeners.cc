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
#include "inter_space.hh"

void loop() {
    add_listeners();
    add_hook(Hook::REFRESH,hook_show_message);

    while(true) {
        char ch = getch();
        bool b = !get_contents()(ch);
        get_contents().refreshmaxyx();
        if(get_contents().refresh) {
            print_contents(get_contents());
        }
        if(b) {
            show_message((std::string("Didn't recognize key press: ")
                          + ch).c_str());
        } else {
            if(!is_showing_message()) {
                int vis_y,vis_x;
                getyx(stdscr,vis_y,vis_x);
                show_message((   "y:" + std::to_string(get_contents().y) + ','
                              + " x:" + std::to_string(get_contents().x) + ','
                              + " vis_y:" + std::to_string(vis_y) + ','
                              + " vis_x:" + std::to_string(vis_x) + ','
                              + " y_offset:" + std::to_string(get_contents().y_offset)
                             ).c_str());
            }
        }
    }
}
