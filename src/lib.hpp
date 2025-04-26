#pragma once

enum class ErrorCode {
    SUCCESS = 0,
    ERROR = 1
};

struct Result {
    ErrorCode ErrorCode;
    std::vector<unsigned int> Numbers;
};

Result parse(const std::string& input) {
    return {
        ErrorCode::ERROR,
        std::vector<unsigned int>{}
    };
}