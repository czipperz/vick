#include <cstdarg>
#include <ncurses.h>

static const char* mes = NULL;
extern bool showing_message;
bool showing_message = false;

static void showmes() {
    int y,x,rows,_;
    getyx(stdscr,y,x);
    getmaxyx(stdscr,rows,_);
    move(rows-1,0);

    clrtoeol();
    printw("%s",mes);

    move(y,x);
}

void hook_show_message() {
    if(showing_message) {
        showmes();
        showing_message = false;
    }
}

void show_message(const char* message) {
    showing_message = true;
    mes = message;
    showmes();
}

void clear_message() {
    mes = "";
    showmes();
}
