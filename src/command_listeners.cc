#include <iostream>
#include <ncurses.h>
#include <map>
#include <string>
#include <stdlib.h>
#include <vector>

#include "configuration.hh"
#include "int_to_str.hh"
#include "key_aliases.hh"
#include "show_message.hh"

static std::map<std::string,
                void (*)(const std::vector<std::string>&)>
    commandMap;
static bool fin = false;

static std::vector<std::string>* getArgs();

void command_executor() {
    if(!fin) { add_commands(commandMap); fin = true; }
    std::vector<std::string>* args = getArgs();
    if(args == NULL) return;
    std::string name = (*args)[0];
    args->erase(args->begin());
    if(commandMap.count(name)) commandMap[name](*args);
    else show_message((std::string("Unrecognized command: ") + name +
                       " with args: " + inter_space(args)).c_str());
}

static std::vector<std::string>* getArgs() {
    int b_y, b_x, m_y, m_x,
        xtrack = 0;
    getyx(stdscr,b_y,b_x);
    getmaxyx(stdscr,m_y,m_x);
    std::vector<std::string>* args = new std::vector<std::string>();
    std::string str;
    char c;
    move(m_y - 1,0);
    addch(':');
    while(true) {
        while(true) {
            c = getch();
            if(c == ERR) {
                endwin();
                exit(2);
            } if(c == '\n') {
                args->push_back(str);
                move(b_y,b_x);
                return args;
            } if(c == ' ') {
                args->push_back(str);
                break;
            } if(c == _escape) {
                timeout(0);//if waiting char then get
                char ch = getch();
                if(ch == -1) {
                    delete args;
                    move(b_y,b_x);
                    return NULL;
                }
                timeout(-1);
            }
            move(m_y-1,++xtrack);
            addch(c);
            str += c;
        }
        str = std::string();
    }
}
