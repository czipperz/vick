#include "catch.hpp"

#include "../src/split.hh"

TEST_CASE("split") {
    auto f = split("\nhi\nbye", '\n');
    REQUIRE(f.size() == 3);
    REQUIRE(f[0] == "");
    REQUIRE(f[1] == "hi");
    REQUIRE(f[2] == "bye");
}
