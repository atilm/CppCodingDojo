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

TEST_CASE("parsing a string with all eights can be parsed") {  
    std::string input = ""
    " _  _  _  _  _  _  _  _  _ \n"
    "|_||_||_||_||_||_||_||_||_|\n"
    "|_||_||_||_||_||_||_||_||_|\n"
    "                           \n";
    std::vector<std::string> expected = {"888888888"};
    auto result = parse(input);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Numbers == expected);
}

TEST_CASE("parsing a string with all digits can be parsed") {  
    std::string input = ""
    "    _  _     _  _  _  _  _ \n"
    "  | _| _||_||_ |_   ||_||_|\n"
    "  ||_  _|  | _||_|  ||_| _|\n"
    "                           \n";
    std::vector<std::string> expected = {"123456789"};
    auto result = parse(input);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Numbers == expected);
}

TEST_CASE("a file with two numbers can be parsed") {  
    std::string input = ""
    "    _  _     _  _  _  _  _ \n"
    "  | _| _||_||_ |_   ||_||_|\n"
    "  ||_  _|  | _||_|  ||_| _|\n"
    "                           \n"
    " _  _  _     _  _  _  _  _ \n"
    " _| _| _||_||_ |_   ||_||_|\n"
    "|_ |_  _|  | _||_|  ||_| _|\n"
    "                           \n";
    std::vector<std::string> expected = {"123456789", "223456789"};
    auto result = parse(input);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Numbers == expected);
}