#pragma once

#include <string>
#include <vector>

enum class ErrorCode {
    SUCCESS = 0,
    ERROR = 1
};

struct Result {
    ErrorCode Status;
    std::vector<std::string> Numbers;
};

Result parse(const std::string& input, bool validate = false, bool auto_correct = false);

bool is_valid(const std::string& number);