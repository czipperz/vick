#include <ncurses.h>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "key_listeners.hh"
#include "file_contents.hh"
#include "configuration.hh"

int main(int argc, char**argv) {
    argc--;argv++;

    initscr();
    noecho();
    raw();

    if(use_colors()) {
        start_color();
    }

    init_conf();

    std::vector<std::string> lines = std::vector<std::string>();
    if(argc) {
        std::string line;
        std::ifstream myfile(argv[0]);
        if(!myfile.good())
            lines.push_back("");
        else while(std::getline(myfile,line))
                 lines.push_back(line);
    } else {
        lines.push_back("");
    }

    init(lines);
    loop();

    endwin();
    return 0;
}
