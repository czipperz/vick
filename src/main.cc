#include <ncurses.h>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "key_listeners.hh"

int main(int argc, char**argv) {
    argc--;argv++;

    std::string line;
    std::vector<std::string>* lines = new std::vector<std::string>;
    std::ifstream myfile(argv[0]);
    while(std::getline(myfile,line))
        lines->push_back(line);

    initscr();
    noecho();
    raw();

    loop(lines);

    endwin();
    return 0;
}
