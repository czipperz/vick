#include <iostream>
#include <ncurses.h>

#include "../src/newmove.hh"
#include "../src/configuration.hh"
#include "catch.hpp"

TEST_CASE("mvsot") {
    contents contents;
    contents.push_back("    hello");

    initscr();
    mvsot(contents);
    endwin();

    REQUIRE(0 ==contents.y);
    REQUIRE(4 ==contents.x);
}

TEST_CASE("mvcol") {
    contents contents;
    contents.push_back("asert");

    initscr();
    mvcol(contents,3);
    int y1 = contents.y,
        x1 = contents.x;

    mvcol(contents,10); //doesn't do anything
    int y2 = contents.y,
        x2 = contents.x;

    mvcol(contents,0);
    int y3 = contents.y,
        x3 = contents.x;
    endwin();

    REQUIRE(0 ==y1);
    REQUIRE(0 ==y2);
    REQUIRE(0 ==y3);
    REQUIRE(3 ==x1);
    REQUIRE(3 ==x2);
    REQUIRE(0 ==x3);
}

TEST_CASE("mvsol") {
    contents contents (0,5);
    contents.push_back("    assert");

    initscr();
    mvsol(contents);
    int y = contents.y,
        x = contents.x;
    endwin();

    REQUIRE(0 ==y);
    REQUIRE(0 ==x);
}

TEST_CASE("mvd") {
    contents contents;
    contents.push_back("assert");
    contents.push_back("hello");
    contents.push_back("aseuirpo");

    initscr();
    mvd(contents,2);
    int y = contents.y,
        x = contents.x;
    mvd(contents);
    int y1 = contents.y,
        x1 = contents.x;
    endwin();

    REQUIRE(0 ==x);
    REQUIRE(0 ==x1);
    REQUIRE(2 ==y);
    REQUIRE(2 ==y1);
}

TEST_CASE("mvf") {
    contents contents;
    contents.push_back("assert");
    contents.push_back("hello");

    initscr();
    mvf(contents,3);
    int y = contents.y,
        x = contents.x;
    mvf(contents,4);
    int y1 = contents.y,
        x1 = contents.x;
    endwin();

    REQUIRE(0 ==y);
    REQUIRE(3 ==x);
    REQUIRE(1 ==y1);
    REQUIRE(1 ==x1);
}

TEST_CASE("mvb") {
    contents contents (1,0);
    contents.push_back("assert");
    contents.push_back("back");

    initscr();
    mvb(contents,2);
    int y = contents.y,
        x = contents.x;
    endwin();

    REQUIRE(0 ==y);
    REQUIRE(4 ==x);
}

TEST_CASE("mvf_2") {
    contents contents;
    contents.push_back("CFLAGS=-lncurses -Wall");
    contents.push_back("O=out");
    contents.push_back("S=src");
    contents.push_back("T=test");
    contents.push_back("TO=testout");
    contents.push_back("CC=g++");

    initscr();
    mveol(contents);
    int y = contents.y,
        x = contents.x;
    mvf(contents,2);
    int y1 = contents.y,
        x1 = contents.x;
    endwin();

    REQUIRE(0 ==y);
    REQUIRE(21 ==x);
    REQUIRE(1 ==y1);
    REQUIRE(1 ==x1);
}

TEST_CASE("mveol") {
    contents contents;
    contents.push_back("Aesop");

    initscr();
    mveol(contents);
    int y = contents.y,
        x = contents.x;
    endwin();

    REQUIRE(4 ==x);
    REQUIRE(0 ==y);
}

TEST_CASE("mvu") {
    contents contents (1,6);
    contents.push_back("hi");
    contents.push_back("Alabama");

    initscr();
    mvu(contents);
    int y1 = contents.y,
        x1 = contents.x;
    endwin();

    REQUIRE(0 ==y1);
    REQUIRE(1 ==x1);
    REQUIRE(true ==contents.waiting_for_desired);
    REQUIRE(6 ==contents.desired_x);
}

TEST_CASE("mvd_2") {
    contents contents;
    contents.push_back("CFLAGS=-lncurses -Wall");
    contents.push_back("O=out");
    contents.push_back("S=src");
    contents.push_back("T=test");

    initscr();
    mveol(contents);
    int y = contents.y,
        x = contents.x;
    mvd(contents);
    int y1 = contents.y,
        x1 = contents.x;
    int d1 = contents.desired_x;
    bool w1 = contents.waiting_for_desired;
    mvd(contents);
    int y2 = contents.y,
        x2 = contents.x;
    int d2 = contents.desired_x;
    bool w2 = contents.waiting_for_desired;
    endwin();

    REQUIRE(0 ==y);
    REQUIRE(21 ==x);

    REQUIRE(1 ==y1);
    REQUIRE(4 ==x1);
    REQUIRE(21 ==d1);
    REQUIRE(true ==w1);

    REQUIRE(2 ==y2);
    REQUIRE(4 ==x2);
    REQUIRE(21 ==d2);
    REQUIRE(true ==w2);
}

TEST_CASE("mvf_over_empty_lines") {
    contents contents (0,1);
    contents.push_back("hi");
    contents.push_back("");
    contents.push_back("hi");

    initscr();
    mvf(contents);
    endwin();

    REQUIRE(0 ==contents.x);
    REQUIRE(1 ==contents.y);
}

TEST_CASE("mvf_over_tabs") {
    contents contents (0,25);
    contents.push_back("testVI: ${files} $O/main.o");
    contents.push_back("\t${CC} -o testVI $^ $(CFLAGS)");

    initscr();
    mvf(contents);
    int vis_y,vis_x,y,x;
    getyx(stdscr,vis_y,vis_x);
    y = contents.y;
    x = contents.x;
    mvf(contents);
    int vis_y1,vis_x1,y1,x1;
    getyx(stdscr,vis_y1,vis_x1);
    y1= contents.y;
    x1= contents.x;
    endwin();

    REQUIRE(1 ==y);
    REQUIRE(0 ==x);
    REQUIRE(1 ==vis_y);
    REQUIRE(7 ==vis_x);
    REQUIRE(1 ==y1);
    REQUIRE(1 ==x1);
    REQUIRE(1 ==vis_y1);
    REQUIRE(8 ==vis_x1);
}

TEST_CASE("to_visual") {
    std::string
        first("assert"),
        second("\tblah");
    for(int i = 0; i < first.size(); i++)
        REQUIRE(i == to_visual(first,i));
    for(int i = 0; i < second.size(); i++)
        REQUIRE(TAB_SIZE() - 1 + i == to_visual(second,i));
}

TEST_CASE("from_visual") {
    std::string
        first("\thi"),
        second("\t\thi");
    for(int i = 1; i < TAB_SIZE() - 1; i++) {
        if(0 != from_visual(first,TAB_SIZE() - i))
            std::cout << i << std::endl;
        REQUIRE(0 == from_visual(first, TAB_SIZE() - i));
    }
    REQUIRE(0 == from_visual(first,TAB_SIZE() - 1));
    REQUIRE(1 == from_visual(first,TAB_SIZE()));
    REQUIRE(2 == from_visual(first,TAB_SIZE() + 1));
}
