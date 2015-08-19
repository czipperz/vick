#include <cstdarg>
#include <ncurses.h>

void show_message(const char* message) {
    int y,x,
        rows,cols;
    getyx(stdscr,y,x);
    getmaxyx(stdscr,rows,cols);

    move(rows-1,0);

    clrtoeol();
    printw(message);

    move(y,x);
}

void clear_message() {
    int y,x,rows,cols;
    getyx(stdscr,y,x);
    getmaxyx(stdscr,rows,cols);
    move(rows-1,0);
    clrtoeol();
    move(y,x);
}
