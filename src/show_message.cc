#include <cstdarg>
#include <ncurses.h>

static const char* mes("");
static bool show(false);

static void showmes() {
    int y,x,rows,_;
    getyx(stdscr,y,x);
    getmaxyx(stdscr,rows,_);
    move(rows-1,0);

    clrtoeol();
    printw(mes);

    move(y,x);
}

void hook_show_message() {
    if(show) {
        showmes();
        show = false;
    }
}

void show_message(const char* message) {
    show = true;
    mes = message;
    showmes();
}

void clear_message() {
    mes = "";
    showmes();
}
