#include "inter_space.hh"
#include "catch.hpp"

TEST_CASE("Test that inter_space works","[inter_space]") {
    std::vector<std::string> vec;
    vec.push_back("first");
    vec.push_back("second");
    vec.push_back("third");
    REQUIRE("first second third" == inter_space(vec));
    std::vector<std::string> empty;
    REQUIRE("" == inter_space(empty));
}
