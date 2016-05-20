/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "catch.hpp"

#include "visual.hh"
#include "configuration.hh"

using namespace vick;

TEST_CASE("to_visual", "[to_visual]") {
    std::string first("assert"), second("\tblah");
    for (size_t i = 0; i < first.size(); i++) {
        REQUIRE(i == to_visual(first, i));
    }
    for (size_t i = 0; i < second.size(); i++) {
        REQUIRE(TAB_SIZE - 1 + i == to_visual(second, i));
    }
}

TEST_CASE("from_visual", "[from_visual]") {
    std::string first("\thi"), second("\t\thi");
    for (move_t i = 1; i < TAB_SIZE - 1; i++) {
        REQUIRE(0 == from_visual(first, TAB_SIZE - i));
    }
    REQUIRE(0 == from_visual(first, TAB_SIZE - 1));
    REQUIRE(1 == from_visual(first, TAB_SIZE));
    REQUIRE(2 == from_visual(first, TAB_SIZE + 1));
}
