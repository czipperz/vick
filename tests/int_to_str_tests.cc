#include "../src/int_to_str.hh"
#include "UnitTest++/UnitTest++.h"

TEST(int_to_str) {
    CHECK_EQUAL("10"      ,int_to_str(10));
    CHECK_EQUAL("-32"     ,int_to_str(-32));
    CHECK_EQUAL("0"       ,int_to_str(0));
    CHECK_EQUAL("5478943" ,int_to_str(5478943));
}

TEST(bool_to_str) {
    CHECK_EQUAL("true" ,bool_to_str(true));
    CHECK_EQUAL("false",bool_to_str(false));
}

TEST(inter_space) {
    std::vector<std::string> vec;
    vec.push_back("first");
    vec.push_back("second");
    vec.push_back("third");
    CHECK_EQUAL("first second third",inter_space(&vec));
}
