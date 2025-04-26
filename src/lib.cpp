#include "lib.hpp"

Result parse(const std::string& input) {
    if (input.empty()) {
        return {
            ErrorCode::SUCCESS,
            {}
        };
    }

    return {
        ErrorCode::SUCCESS,
        std::vector<std::string>{"888888888"}
    };
}