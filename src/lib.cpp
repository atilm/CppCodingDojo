#include "lib.hpp"
#include <array>

typedef unsigned char segment_mask;

Result parse(const std::string& input) {
    if (input.empty()) {
        return {
            ErrorCode::SUCCESS,
            {}
        };
    }

    std::array<segment_mask, 9> digit_masks = {0};

    unsigned int row = 0;
    unsigned int col = 0;

    for (char c : input) {
        if (c == '\n') {
            row++;
            col = 0;
            continue;
        }

        unsigned int sub_row = row % 4;
        unsigned int sub_col = col % 3;
        unsigned int digit_index = col / 3;

        switch (sub_row) {
            case 0:
                switch (c) {
                    case ' ':
                        break;
                    case '_':
                        if (sub_col == 1) {
                            digit_masks[digit_index] |= 0b00000001;
                        }
                        break;
                    case '|':
                        break;
                    default:
                        break;
                }
                break;
            case 1:
            switch (c) {
                case ' ':
                    break;
                case '_':
                    if (sub_col == 1) {
                        digit_masks[digit_index] |= 1 << 2;
                    }
                    break;
                case '|':
                    if (sub_col == 0) {
                        digit_masks[digit_index] |= 1 << 1;
                    } else if (sub_col == 2) {
                        digit_masks[digit_index] |= 1 << 3;
                    }
                    break;
                default:
                    break;
            }
                break;
            case 2:
                switch (c) {
                    case ' ':
                        break;
                    case '_':
                        if (sub_col == 1) {
                            digit_masks[digit_index] |= 1 << 5;
                        }
                        break;
                    case '|':
                        if (sub_col == 0) {
                            digit_masks[digit_index] |= 1 << 4;
                        } else if (sub_col == 2) {
                            digit_masks[digit_index] |= 1 << 6;
                        }
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                break;
            default:
                break;
        }

        col++;
    }

    constexpr segment_mask EIGHT_SEGMENTS = 0b1111111;
    std::string result;

    for (auto& mask : digit_masks) {
        if (mask == EIGHT_SEGMENTS) {
            result += '8';
        } else {
            result += '?';
        }
    }

    return {
        ErrorCode::SUCCESS,
        std::vector<std::string>{result}
    };
}