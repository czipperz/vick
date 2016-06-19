/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "catch.hpp"

#include "split.hh"

using namespace vick;

TEST_CASE("split empty string", "[split]") {
    REQUIRE(split("", '\n').size() == 0);
}

TEST_CASE("split that does nothing", "[split]") {
    auto s = split("hi bye", '\n');
    REQUIRE(s.size() == 1);
    REQUIRE(s[0] == "hi bye");
}

TEST_CASE("split", "[split]") {
    auto s = split("\nhi\nbye", '\n');
    REQUIRE(s.size() == 3);
    REQUIRE(s[0] == "");
    REQUIRE(s[1] == "hi");
    REQUIRE(s[2] == "bye");
}

TEST_CASE("split ending \\n", "[split]") {
    auto s = split("\nhi\nbye\n", '\n');
    REQUIRE(s.size() == 4);
    REQUIRE(s[0] == "");
    REQUIRE(s[1] == "hi");
    REQUIRE(s[2] == "bye");
    REQUIRE(s[3] == "");
}

TEST_CASE("split_by_line empty string", "[split]") {
    REQUIRE(split_by_line("").size() == 0);
}

TEST_CASE("split_by_line that does nothing", "[split]") {
    auto s = split_by_line("hi bye");
    REQUIRE(s.size() == 1);
    REQUIRE(s[0] == "hi bye");
}

TEST_CASE("split_by_line", "[split]") {
    auto s = split_by_line("\nhi\nbye");
    REQUIRE(s.size() == 3);
    REQUIRE(s[0] == "");
    REQUIRE(s[1] == "hi");
    REQUIRE(s[2] == "bye");
}

TEST_CASE("split_by_line ending \\n", "[split]") {
    auto s = split_by_line("\nhi\nbye\n");
    REQUIRE(s.size() == 4);
    REQUIRE(s[0] == "");
    REQUIRE(s[1] == "hi");
    REQUIRE(s[2] == "bye");
    REQUIRE(s[3] == "");
}

TEST_CASE("split_by_line \\r no starting \\r\\n", "[split]") {
    auto s = split_by_line("hi\r\nbye");
    REQUIRE(s.size() == 2);
    REQUIRE(s[0] == "hi");
    REQUIRE(s[1] == "bye");
}

TEST_CASE("split_by_line \\r", "[split]") {
    auto s = split_by_line("\r\nhi\r\nbye");
    REQUIRE(s.size() == 3);
    REQUIRE(s[0] == "");
    REQUIRE(s[1] == "hi");
    REQUIRE(s[2] == "bye");
}

TEST_CASE("split_by_line \\r ending \\n", "[split]") {
    auto s = split_by_line("\r\nhi\r\nbye\r\n");
    REQUIRE(s.size() == 4);
    REQUIRE(s[0] == "");
    REQUIRE(s[1] == "hi");
    REQUIRE(s[2] == "bye");
    REQUIRE(s[3] == "");
}
