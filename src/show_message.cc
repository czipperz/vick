#include <cstdarg>
#include <ncurses.h>
#include <string>

namespace vick {

static std::string mes;
extern bool showing_message;
bool showing_message = false;

static void showmes() {
    int y,x,rows,_;
    getyx(stdscr,y,x);
    getmaxyx(stdscr,rows,_);
    move(rows-1,0);

    clrtoeol();
    attron(COLOR_PAIR(1));
    printw("%s", mes.c_str());
    attroff(COLOR_PAIR(1));

    move(y,x);
}

void hook_show_message() {
    if(showing_message) {
        showmes();
        showing_message = false;
    }
}

void show_message(std::string message) {
    showing_message = true;
    mes = message;
    showmes();
}

void clear_message() {
    showing_message = false;
    mes = "";
    showmes();
}

}
