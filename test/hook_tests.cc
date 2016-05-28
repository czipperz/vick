/* Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/ */

#include "catch.hpp"

#include "hooks.hh"

static int i;
static void inc_i(vick::contents&) { ++i; }

TEST_CASE("hook proc", "[hook]") {
    vick::hook h;
    vick::contents c;
    h.add(inc_i);
    int li = i;
    h.proc(c);
    REQUIRE(li + 1 == i);
}

TEST_CASE("hook remove", "[hook]") {
    vick::hook h;
    vick::contents c;
    int li = i;
    h.add(inc_i);
    REQUIRE(li == i);
    h.proc(c);
    REQUIRE(li + 1 == i);
    REQUIRE(h.remove(inc_i));
    REQUIRE_FALSE(h.remove(inc_i));
    REQUIRE(li + 1 == i);
    h.proc(c);
    REQUIRE(li + 1 == i);
}

TEST_CASE("hook add multiple", "[hook]") {
    vick::hook h;
    vick::contents c;
    int li = i;
    h.add(inc_i);
    h.add(inc_i);
    REQUIRE(li == i);
    h.proc(c);
    REQUIRE(li + 2 == i);
    REQUIRE(h.remove(inc_i));
    REQUIRE_FALSE(h.remove(inc_i));
    REQUIRE(li + 2 == i);
    h.proc(c);
    REQUIRE(li + 2 == i);
}
