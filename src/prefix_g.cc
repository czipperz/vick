#include <map>
#include <ncurses.h>
#include <string>
#include <functional>

#include "mode.hh"
#include "move.hh"
#include "prefix_g.hh"
#include "show_message.hh"

static std::map < char, std::function<void ()> > prefix_g_map;

void setup_prefix_g() {
    global_normal_map['g'] = prefix_g;
    prefix_g_map['g'] = mvsop;
}

void prefix_g() {
    char ch = getch();
    auto it = prefix_g_map.find(ch);
    if(it == prefix_g_map.end()) {
        show_message((std::string("Didn't recognize key press inside `g': ")
                      + ch).c_str());
    } else {
        it->second();
    }
}
