/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "catch.hpp"

#include "inter_space.hh"

using namespace vick;

TEST_CASE("Test that inter_space works", "[inter_space]")
{
    std::vector<std::string> vec;
    vec.push_back("first");
    vec.push_back("second");
    vec.push_back("third");
    REQUIRE("first second third" == inter_space(vec));
    std::vector<std::string> empty;
    REQUIRE("" == inter_space(empty));
}
