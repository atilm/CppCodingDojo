#include "lib.hpp"
#include <array>

typedef unsigned char segment_mask;

class DigitMask {
    public:

    void set_segment(unsigned int segment) {
        if (segment < 7) {
            mask |= (1 << segment);
        }
    }

    bool operator==(const segment_mask other) const {
        return mask == other;    
    }

    private:
    segment_mask mask = 0;
};

Result parse(const std::string& input) {
    if (input.empty()) {
        return {
            ErrorCode::SUCCESS,
            {}
        };
    }

    std::array<DigitMask, 9> digit_masks;

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
                            digit_masks[digit_index].set_segment(0);
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
                        digit_masks[digit_index].set_segment(2);
                    }
                    break;
                case '|':
                    if (sub_col == 0) {
                        digit_masks[digit_index].set_segment(1);
                    } else if (sub_col == 2) {
                        digit_masks[digit_index].set_segment(3);
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
                            digit_masks[digit_index].set_segment(5);
                        }
                        break;
                    case '|':
                        if (sub_col == 0) {
                            digit_masks[digit_index].set_segment(4);
                        } else if (sub_col == 2) {
                            digit_masks[digit_index].set_segment(6);
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