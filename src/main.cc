#include <algorithm>
#include <fstream>
#include <iterator>
#include <ncurses.h>
#include <string>
#include <vector>

#include "configuration.hh"
#include "file_contents.hh"
#include "key_listeners.hh"

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
