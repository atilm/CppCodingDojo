#include "lib.hpp"
#include <array>
#include <map>

typedef unsigned char segment_mask;

class DigitMask
{
public:
    void set_segment(unsigned int segment)
    {
        if (segment < 7)
        {
            mask |= (1 << segment);
        }
    }

    segment_mask get_mask() const
    {
        return mask;
    }

    bool operator==(const segment_mask other) const
    {
        return mask == other;
    }

private:
    segment_mask mask = 0;
};

struct Segment
{
    unsigned int index;
    char c;
    unsigned int row;
    unsigned int col;

    bool matches(char c, unsigned int row, unsigned int col) const
    {
        return this->c == c && this->row == row && this->col == col;
    }
};

constexpr Segment segments[7] = {
    {0, '_', 0, 1},
    {1, '|', 1, 0},
    {2, '_', 1, 1},
    {3, '|', 1, 2},
    {4, '|', 2, 0},
    {5, '_', 2, 1},
    {6, '|', 2, 2}};

const std::map<segment_mask, char> DIGIT_MAP = {
    {0b1001000, '1'}, // 1
    {0b0111101, '2'}, // 2
    {0b1101101, '3'}, // 3
    {0b1001110, '4'}, // 4
    {0b1100111, '5'}, // 5
    {0b1110111, '6'}, // 6
    {0b1001001, '7'}, // 7
    {0b1111111, '8'}, // 8
    {0b1101111, '9'}  // 9
};

class ParserStateMachine
{
public:
    void next(char c)
    {
        unsigned int sub_row = row % 4;
        unsigned int sub_col = col % 3;
        unsigned int digit_index = col / 3;

        for (const auto &segment : segments)
        {
            if (segment.matches(c, sub_row, sub_col))
            {
                digit_masks[digit_index].set_segment(segment.index);
                break;
            }
        }

        col++;
        if (c == '\n')
        {
            row++;
            col = 0;
        }
    }

    const std::array<DigitMask, 9> &get_digit_masks() const
    {
        return digit_masks;
    }

private:
    unsigned int row = 0;
    unsigned int col = 0;
    std::array<DigitMask, 9> digit_masks;
};

Result parse(const std::string &input)
{
    if (input.empty())
    {
        return {
            ErrorCode::SUCCESS,
            {}};
    }

    std::vector<std::string> numbers;

    ParserStateMachine parser;
    for (char c : input)
    {
        parser.next(c);
    }

    std::string result;

    auto &digit_masks = parser.get_digit_masks();
    for (auto &mask : digit_masks)
    {
        if (DIGIT_MAP.contains(mask.get_mask()))
        {
            result += DIGIT_MAP.at(mask.get_mask());
        }
        else
        {
            result += '?';
        }
    }

    numbers.emplace_back(result);

    return {
        ErrorCode::SUCCESS,
        numbers};
}