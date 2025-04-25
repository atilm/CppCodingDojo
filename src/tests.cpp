#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "lib.hpp"


TEST_CASE("add function test") {
    REQUIRE(add(1, 2) == 3);
    REQUIRE(add(-1, -1) == -2);
    REQUIRE(add(0, 0) == 0);
    REQUIRE(add(100, 200) == 300);
}