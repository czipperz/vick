#include <map>
#include <ncurses.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "show_message.hh"
#include "parse_init_contents.hh"

static std::map<char,void (*)()> listeners;
static std::vector<std::string>* contents;

void loop(std::vector<std::string>* arg) {
    contents = arg;
    print_init_contents(contents);
    add_listeners(listeners);

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

std::vector<std::string>* get_contents() { return contents; }
