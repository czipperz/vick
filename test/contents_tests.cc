/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "contents.hh"
#include "catch.hpp"

using namespace vick;

TEST_CASE("contents construction coordinates", "[contents]") {
#define TESTS                                                        \
    /* always start at `y = 0`, `x = 0` */                           \
    do {                                                             \
        REQUIRE(c.y == 0);                                           \
        REQUIRE(c.x == 0);                                           \
    } while (0)

    SECTION("contents()") {
        contents c;
        TESTS;
    }
    SECTION("contents({})") {
        contents c({});
        TESTS;
    }
    SECTION("contents({\"hi\", \"bye\"})") {
        contents c({"hi", "bye"});
        TESTS;
    }

#undef TESTS
}

TEST_CASE("contents::push_back", "[contents]") {
    contents c;
    REQUIRE(c.cont.size() == 0);
    c.push_back("hello");
    c.push_back("world");
    REQUIRE(c.cont.size() == 2);
    REQUIRE(c.cont[0] == "hello");
    REQUIRE(c.cont[1] == "world");
}

TEST_CASE("contents::yx", "[contents]") {
    contents c;

    c.waiting_for_desired = false;
    // require that it moves out of bounds without checking
    c.yx(3, 1);
    REQUIRE(c.y == 3);
    REQUIRE(c.x == 1);
    REQUIRE_FALSE(c.waiting_for_desired);

    // ensure it doesn't modify waiting_for_desired
    c.waiting_for_desired = true;
    c.yx(0, 5);
    REQUIRE(c.y == 0);
    REQUIRE(c.x == 5);
    REQUIRE(c.waiting_for_desired);
}

TEST_CASE("contents `copy/move` `assignment/construction`",
          "[contents]") {
    contents n({"asdf", "jkl;"});
    n.yx(1, 1);

#define TESTS                                                        \
    do {                                                             \
        REQUIRE(c.y == 1);                                           \
        REQUIRE(c.x == 1);                                           \
        REQUIRE(c.cont.size() == 2);                                 \
        REQUIRE(c.cont[0] == "asdf");                                \
        REQUIRE(c.cont[1] == "jkl;");                                \
    } while (0)

    SECTION("copy assignment") {
        contents c;
        c = n;
        TESTS;
    }
    SECTION("move assignment") {
        contents c;
        c = std::move(n);
        TESTS;
    }
    SECTION("copy construction") {
        contents c(n);
        TESTS;
    }
    SECTION("move construction") {
        contents c(std::move(n));
        TESTS;
    }

#undef TESTS
}
