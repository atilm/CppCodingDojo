#pragma once

#include <string>
#include <vector>

enum class ErrorCode {
    SUCCESS = 0,
    ERROR = 1
};

struct Result {
    ErrorCode Status;
    std::vector<unsigned int> Numbers;
};

Result parse(const std::string& input);