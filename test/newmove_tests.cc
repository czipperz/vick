#include <iostream>
#include <ncurses.h>

#include "../src/newmove.hh"
#include "UnitTest++/UnitTest++.h"
#include "../src/configuration.hh"

TEST(mvsot) {
    contents contents;
    contents.push_back("    hello");

    initscr();
    mvsot(contents);
    endwin();

    CHECK_EQUAL(0,contents.get_y());
    CHECK_EQUAL(4,contents.get_x());
}

TEST(mvcol) {
    contents contents;
    contents.push_back("asert");

    initscr();
    mvcol(contents,3);
    int y1 = contents.get_y(),
        x1 = contents.get_x();

    mvcol(contents,10); //doesn't do anything
    int y2 = contents.get_y(),
        x2 = contents.get_x();

    mvcol(contents,0);
    int y3 = contents.get_y(),
        x3 = contents.get_x();
    endwin();

    CHECK_EQUAL(0,y1);
    CHECK_EQUAL(0,y2);
    CHECK_EQUAL(0,y3);
    CHECK_EQUAL(3,x1);
    CHECK_EQUAL(3,x2);
    CHECK_EQUAL(0,x3);
}

TEST(mvsol) {
    contents contents (0,5);
    contents.push_back("    assert");

    initscr();
    mvsol(contents);
    int y = contents.get_y(),
        x = contents.get_x();
    endwin();

    CHECK_EQUAL(0,y);
    CHECK_EQUAL(0,x);
}

TEST(mvd) {
    contents contents;
    contents.push_back("assert");
    contents.push_back("hello");
    contents.push_back("aseuirpo");

    initscr();
    mvd(contents,2);
    int y = contents.get_y(),
        x = contents.get_x();
    mvd(contents);
    int y1 = contents.get_y(),
        x1 = contents.get_x();
    endwin();

    CHECK_EQUAL(0,x);
    CHECK_EQUAL(0,x1);
    CHECK_EQUAL(2,y);
    CHECK_EQUAL(2,y1);
}

TEST(mvf) {
    contents contents;
    contents.push_back("assert");
    contents.push_back("hello");

    initscr();
    mvf(contents,3);
    int y = contents.get_y(),
        x = contents.get_x();
    mvf(contents,4);
    int y1 = contents.get_y(),
        x1 = contents.get_x();
    endwin();

    CHECK_EQUAL(0,y);
    CHECK_EQUAL(3,x);
    CHECK_EQUAL(1,y1);
    CHECK_EQUAL(1,x1);
}

TEST(mvb) {
    contents contents (1,0);
    contents.push_back("assert");
    contents.push_back("back");

    initscr();
    mvb(contents,2);
    int y = contents.get_y(),
        x = contents.get_x();
    endwin();

    CHECK_EQUAL(0,y);
    CHECK_EQUAL(4,x);
}

TEST(mvf_2) {
    contents contents;
    contents.push_back("CFLAGS=-lncurses -Wall");
    contents.push_back("O=out");
    contents.push_back("S=src");
    contents.push_back("T=test");
    contents.push_back("TO=testout");
    contents.push_back("CC=g++");

    initscr();
    mveol(contents);
    int y = contents.get_y(),
        x = contents.get_x();
    mvf(contents,2);
    int y1 = contents.get_y(),
        x1 = contents.get_x();
    endwin();

    CHECK_EQUAL(0,y);
    CHECK_EQUAL(21,x);
    CHECK_EQUAL(1,y1);
    CHECK_EQUAL(1,x1);
}

TEST(mveol) {
    contents contents;
    contents.push_back("Aesop");

    initscr();
    mveol(contents);
    int y = contents.get_y(),
        x = contents.get_x();
    endwin();

    CHECK_EQUAL(4,x);
    CHECK_EQUAL(0,y);
}

TEST(mvu) {
    contents contents (1,6);
    contents.push_back("hi");
    contents.push_back("Alabama");

    initscr();
    mvu(contents);
    int y1 = contents.get_y(),
        x1 = contents.get_x();
    endwin();

    CHECK_EQUAL(0,y1);
    CHECK_EQUAL(1,x1);
    CHECK_EQUAL(true,contents.get_waiting_for_desired());
    CHECK_EQUAL(6,contents.get_desired_x());
}

TEST(mvd_2) {
    contents contents;
    contents.push_back("CFLAGS=-lncurses -Wall");
    contents.push_back("O=out");
    contents.push_back("S=src");
    contents.push_back("T=test");

    initscr();
    mveol(contents);
    int y = contents.get_y(),
        x = contents.get_x();
    mvd(contents);
    int y1 = contents.get_y(),
        x1 = contents.get_x();
    int d1 = contents.get_desired_x();
    bool w1 = contents.get_waiting_for_desired();
    mvd(contents);
    int y2 = contents.get_y(),
        x2 = contents.get_x();
    int d2 = contents.get_desired_x();
    bool w2 = contents.get_waiting_for_desired();
    endwin();

    CHECK_EQUAL(0,y);
    CHECK_EQUAL(21,x);

    CHECK_EQUAL(1,y1);
    CHECK_EQUAL(4,x1);
    CHECK_EQUAL(21,d1);
    CHECK_EQUAL(true,w1);

    CHECK_EQUAL(2,y2);
    CHECK_EQUAL(4,x2);
    CHECK_EQUAL(21,d2);
    CHECK_EQUAL(true,w2);
}

TEST(mvf_over_empty_lines) {
    contents contents (0,1);
    contents.push_back("hi");
    contents.push_back("");
    contents.push_back("hi");

    initscr();
    mvf(contents);
    endwin();

    CHECK_EQUAL(0,contents.get_x());
    CHECK_EQUAL(1,contents.get_y());
}

TEST(mvf_over_tabs) {
    contents contents (0,25);
    contents.push_back("testVI: ${files} $O/main.o");
    contents.push_back("\t${CC} -o testVI $^ $(CFLAGS)");

    initscr();
    mvf(contents);
    int vis_y,vis_x,y,x;
    getyx(stdscr,vis_y,vis_x);
    y = contents.get_y();
    x = contents.get_x();
    mvf(contents);
    int vis_y1,vis_x1,y1,x1;
    getyx(stdscr,vis_y1,vis_x1);
    y1= contents.get_y();
    x1= contents.get_x();
    endwin();

    CHECK_EQUAL(1,y);
    CHECK_EQUAL(0,x);
    CHECK_EQUAL(1,vis_y);
    CHECK_EQUAL(6,vis_x);

    std::cout << "break\n";
    CHECK_EQUAL(1,y1);
    CHECK_EQUAL(1,x1);
    CHECK_EQUAL(1,vis_y1);
    CHECK_EQUAL(7,vis_x1);
}

TEST(to_visual) {
    std::string first("\thi");
    CHECK_EQUAL(TAB_SIZE() - 1, to_visual(first,0));
}
