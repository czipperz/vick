#include "catch.hpp"

#include "visual.hh"
#include "configuration.hh"

using namespace vick;

TEST_CASE("to_visual") {
    std::string
        first("assert"),
        second("\tblah");
    for(int i = 0; i < first.size(); i++)
        REQUIRE(i == to_visual(first,i));
    for(int i = 0; i < second.size(); i++)
        REQUIRE(TAB_SIZE - 1 + i == to_visual(second,i));
}

TEST_CASE("from_visual") {
    std::string
        first("\thi"),
        second("\t\thi");
    for(int i = 1; i < TAB_SIZE - 1; i++) {
        REQUIRE(0 == from_visual(first, TAB_SIZE - i));
    }
    REQUIRE(0 == from_visual(first,TAB_SIZE - 1));
    REQUIRE(1 == from_visual(first,TAB_SIZE));
    REQUIRE(2 == from_visual(first,TAB_SIZE + 1));
}
