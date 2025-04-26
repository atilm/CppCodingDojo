#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "lib.hpp"

TEST_CASE("parsing an empty string returns an empty vector") {  
    std::string input = "";
    std::vector<std::string> expected = {};
    auto result = parse(input);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Numbers == expected);
}

TEST_CASE("parsing a string with one number returns a vector with that number") {  
    std::string input = ""
    "                           \n"
    "  |                        \n"
    "  |                        \n"
    "                           \n";
    std::vector<std::string> expected = {"1        "};
    auto result = parse(input);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Numbers == expected);
}