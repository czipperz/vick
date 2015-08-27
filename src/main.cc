#include <ncurses.h>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "key_listeners.hh"
#include "file_contents.hh"

int main(int argc, char**argv) {
    argc--;argv++;

    std::vector<std::string> lines = std::vector<std::string>();
    if(argc) {
        std::string line;
        std::ifstream myfile(argv[0]);
        while(std::getline(myfile,line))
            lines.push_back(line);
    } else {
        lines.push_back("");
    }

    initscr();
    noecho();
    raw();

    init(lines);
    loop();

    endwin();
    return 0;
}
