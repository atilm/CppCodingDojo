#pragma once

#include <string>
#include <vector>

enum class ErrorCode {
    SUCCESS = 0,
    ERROR = 1
};

template <typename T, typename U>
struct Result {
    T Status;
    U Value;
};

Result<ErrorCode, std::vector<std::string>> parse(const std::string& input, bool validate = false, bool auto_correct = false);

bool is_valid(const std::string& number);