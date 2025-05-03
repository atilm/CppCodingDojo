#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "lib.hpp"

TEST_CASE("parsing an empty string returns an empty vector") {  
    std::string input = "";
    std::vector<std::string> expected = {};
    auto result = parse(input);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Value == expected);
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
    REQUIRE(result.Value == expected);
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
    REQUIRE(result.Value == expected);
}

TEST_CASE("a file with two numbers can be parsed") {  
    std::string input = ""
    "    _  _     _  _  _  _  _ \n"
    "  | _| _||_||_ |_   ||_||_|\n"
    "  ||_  _|  | _||_|  ||_| _|\n"
    "                           \n"
    " _  _  _     _  _  _  _  _ \n"
    "| | _| _||_||_ |_   ||_||_|\n"
    "|_||_  _|  | _||_|  ||_| _|\n"
    "                           \n";
    std::vector<std::string> expected = {"123456789", "023456789"};
    auto result = parse(input);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Value == expected);
}

TEST_CASE("a number can be validated correctly") {
    bool result = is_valid("345882865");
    REQUIRE(result == true);
}

TEST_CASE("illegible and invalid numbers are marked in the result") {
    std::string input = ""
    "    _  _  _  _  _  _  _  _ \n"
    "|_||_   ||_ | ||_|| || || |\n"
    "  | _|  | _||_||_||_||_||_|\n"
    "                           \n"
    " _  _     _  _        _  _ \n"
    "|_ |_ |_| _|  |  ||_||_||_ \n"
    "|_||_|  | _|  |  |  | _| _|\n"
    "                           \n"
    " _  _        _  _  _  _  _ \n"
    "|_||_   |  || | _||_| _||_ \n"
    "|_||_|  |  ||_||_|| | _||_|\n"
    "                           \n";
    std::vector<std::string> expected = {"457508000", "664371495 ERR", "86110??36 ILL"};
    auto result = parse(input, true);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Value == expected);
}

TEST_CASE("one ill segment can be auto-corrected") {  
    std::string input = ""
    " _  _  _  _  _  _  _  _  _ \n"
    "|_||_||_||_||_||_||_||_||_|\n"
    "|_||_||_|| ||_||_||_||_||_|\n"
    "                           \n";
    std::vector<std::string> expected = {"888888888"};
    auto result = parse(input, false, true);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Value == expected);
}

TEST_CASE("ambiguous segments are recognized by auto correction") {  
    std::string input = ""
    " _  _  _  _  _  _  _  _  _ \n"
    "|_||_||_||_||_| _||_||_||_|\n"
    "|_||_||_||_||_||_||_||_||_|\n"
    "                           \n";
    std::vector<std::string> expected = {"88888?888 AMB"};
    auto result = parse(input, true, true);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Value == expected);
}

TEST_CASE("illegible digits override ambiguous segments in error message") {  
    std::string input = ""
    " _  _  _  _  _  _  _  _  _ \n"
    "|_||_||_||_||   _||_||_||_|\n"
    "|_||_||_||_||  |_||_||_||_|\n"
    "                           \n";
    std::vector<std::string> expected = {"8888??888 ILL"};
    auto result = parse(input, true, true);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Value == expected);
}

TEST_CASE("numbers which don't pass validation can be auto-corrected") {
    std::string input = ""
    "    _  _  _  _  _  _  _  _ \n"
    "|_||_   ||_ | ||_|| || || |\n"
    "  | _|  ||_||_||_||_||_||_|\n";
    std::vector<std::string> expected = {"457508000"};
    auto result = parse(input, true, true);
    REQUIRE(result.Status == ErrorCode::SUCCESS);
    REQUIRE(result.Value == expected);
}
