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


class ParserStateMachine {
    public:

    void next(char c) {
        if (c == '\n') {
            row++;
            col = 0;
            return;
        }

        sub_row = row % 4;
        sub_col = col % 3;
        digit_index = col / 3;

        switch (sub_row) {
            case 0:
                handle_row_0(c);
                break;
            case 1:
                handle_row_1(c);
                break;
            case 2:
                // switch (c) {
                //     case ' ':
                //         break;
                //     case '_':
                //         if (sub_col == 1) {
                //             digit_masks[digit_index].set_segment(5);
                //         }
                //         break;
                //     case '|':
                //         if (sub_col == 0) {
                //             digit_masks[digit_index].set_segment(4);
                //         } else if (sub_col == 2) {
                //             digit_masks[digit_index].set_segment(6);
                //         }
                //         break;
                //     default:
                //         break;
                // }
                handle_row_2(c);
                break;
            case 3:
                break;
            default:
                break;
        }

        col++;
    }

    void handle_row_0(char c) {
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
    }

    void handle_row_1(char c) {
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
    }

    void handle_row_2(char c) {
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
    }

    const std::array<DigitMask, 9>& get_digit_masks() const {
        return digit_masks;
    }
    
    private:
    unsigned int row = 0;
    unsigned int col = 0;
    unsigned int sub_row = 0;
    unsigned int sub_col = 0;
    unsigned int digit_index = 0;
    std::array<DigitMask, 9> digit_masks;
};

Result parse(const std::string& input) {
    if (input.empty()) {
        return {
            ErrorCode::SUCCESS,
            {}
        };
    }

    ParserStateMachine parser;

    for (char c : input) {
        parser.next(c);
    }

    constexpr segment_mask EIGHT_SEGMENTS = 0b1111111;
    std::string result;

    auto& digit_masks = parser.get_digit_masks();
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