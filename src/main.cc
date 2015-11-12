#include <algorithm>
#include <fstream>
#include <iterator>
#include <ncurses.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "file_contents.hh"
#include "key_listeners.hh"
#include "prompt.hh"

int main(int argc, char**argv) {
    using namespace vick;

    argc--;argv++;

    initscr();
    noecho();
    raw();

    if(use_colors()) {
        start_color();
    }

    init_conf();

    bool windows = false;
    std::vector<std::string> lines = std::vector<std::string>();
    if(argc) {
        bool asked = false;
        std::string line;
        std::ifstream myfile(argv[0]);
        if (std::getline(myfile, line)) {
            if (not line.empty() and line.back() == 13) {
                line.pop_back();
                windows = true;
            }
            lines.push_back(line);
            while (std::getline(myfile, line)) {
                if (not line.empty() and line.back() == 13) {
                    if (not windows and not asked) {
                        asked = true;
                        windows = prompt_yes_no("Windows file endings detected, use them when saving? ");
                    }
                    line.pop_back();
                }
                lines.push_back(line);
            }
        }
        else
            goto empty;
    }
    else {
    empty:
        lines.push_back("");
    }

    init(lines, windows);
    loop();

    endwin();
    return 0;
}
