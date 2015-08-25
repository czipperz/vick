#include "../src/int_to_str.hh"
#include "catch.hpp"

TEST_CASE("Test some int_to_str cases","[int_to_str]") {
    REQUIRE("10"      == int_to_str(10));
    REQUIRE("-32"     == int_to_str(-32));
    REQUIRE("0"       == int_to_str(0));
    REQUIRE("5478943" == int_to_str(5478943));
}

TEST_CASE("Test bool_to_str works correctly","[bool_to_str]") {
    REQUIRE("true"  == bool_to_str(true));
    REQUIRE("false" == bool_to_str(false));
}

TEST_CASE("Test that inter_space works","[inter_space]") {
    std::vector<std::string> vec;
    vec.push_back("first");
    vec.push_back("second");
    vec.push_back("third");
    REQUIRE("first second third" == inter_space(&vec));
    std::vector<std::string> empty;
    REQUIRE("" == inter_space(&empty));
}
