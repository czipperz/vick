#include "../src/newmove.hh"
#include "UnitTest++/UnitTest++.h"
#include <ncurses.h>

TEST(mvsot) {
    std::vector<std::string> contents;
    contents.push_back("    hello");

    initscr();
    mvsop(&contents);
    int y,x;
    mvsot(&contents);
    getyx(stdscr,y,x);
    endwin();

    CHECK_EQUAL(0,y);
    CHECK_EQUAL(4,x);
}

TEST(mvcol) {
    std::vector<std::string> contents;
    contents.push_back("asert");

    initscr();
    mvsop(&contents);
    int y1,x1,y2,x2,y3,x3;
    mvcol(&contents,3);
    getyx(stdscr,y1,x1);

    mvcol(&contents,10); //doesn't do anything
    getyx(stdscr,y2,x2);

    mvcol(&contents,0);
    getyx(stdscr,y3,x3);
    endwin();

    CHECK_EQUAL(0,y1);
    CHECK_EQUAL(0,y2);
    CHECK_EQUAL(0,y3);
    CHECK_EQUAL(3,x1);
    CHECK_EQUAL(3,x2);
    CHECK_EQUAL(0,x3);
}

TEST(mvsol) {
    std::vector<std::string> contents;
    contents.push_back("    assert");

    initscr();
    mvsop(&contents);
    int y,x;
    mvsot(&contents);
    mvsol(&contents);
    getyx(stdscr,y,x);
    endwin();

    CHECK_EQUAL(0,y);
    CHECK_EQUAL(0,x);
}

TEST(mvd) {
    std::vector<std::string> contents;
    contents.push_back("assert");
    contents.push_back("hello");
    contents.push_back("aseuirpo");

    initscr();
    mvsop(&contents);
    int y,x,y1,x1;
    mvd(&contents,2);
    getyx(stdscr,y,x);
    mvd(&contents);
    getyx(stdscr,y1,x1);
    endwin();

    CHECK_EQUAL(0,x);
    CHECK_EQUAL(0,x1);
    CHECK_EQUAL(2,y);
    CHECK_EQUAL(2,y1);
}

TEST(mvf) {
    std::vector<std::string> contents;
    contents.push_back("assert");
    contents.push_back("hello");

    initscr();
    mvsop(&contents);
    int y,x,y1,x1;
    mvf(&contents,3); //(0,3)
    getyx(stdscr,y,x);
    mvf(&contents,4); //(1,1)
    getyx(stdscr,y1,x1);
    endwin();

    CHECK_EQUAL(0,y);
    CHECK_EQUAL(3,x);
    CHECK_EQUAL(1,y1);
    CHECK_EQUAL(1,x1);
}

TEST(mvb) {
    std::vector<std::string> contents;
    contents.push_back("assert");
    contents.push_back("back");

    initscr();
    mvsop(&contents);
    int y,x;
    mvd(&contents);
    mvb(&contents,2);
    getyx(stdscr, y, x);
    endwin();

    CHECK_EQUAL(0,y);
    CHECK_EQUAL(4,x);
}

TEST(mveol) {
    std::vector<std::string> contents;
    contents.push_back("aseruiop");

    initscr();
    mvsop(&contents);
    int y,x;
    mveol(&contents);
    getyx(stdscr,y,x);
    endwin();

    CHECK_EQUAL(7,x);
    CHECK_EQUAL(0,y);
}
