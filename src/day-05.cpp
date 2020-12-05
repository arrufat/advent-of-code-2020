#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-05/input");
    std::vector<std::string> input;
    for (std::string line; std::getline(fin, line);)
        input.push_back(line);

    struct range
    {
        range() = default;
        range(int first, int last) : first(first), last(last) {}
        int first = 0;
        int last = 127;
        auto length() const -> int { return last - first + 1; };
    };

    std::vector<int> seat_ids;
    for (const auto& line : input)
    {
        auto row_range = range(0, 127);
        auto col_range = range(0, 7);
        for (size_t i = 0; i < 7; ++i)
        {
            switch (line[i])
            {
            case 'F':
                row_range.last = row_range.first + (row_range.length() - 1) / 2;
                break;
            case 'B':
                row_range.first = row_range.first + row_range.length() / 2;
                break;
            default:
                throw std::out_of_range(&"unknown position "[line[i]]);
            }
        }
        for (size_t i = 7; i < 10; ++i)
        {
            switch (line[i])
            {
            case 'L':
                col_range.last = col_range.first + (col_range.length() - 1) / 2;
                break;
            case 'R':
                col_range.first = col_range.first + col_range.length() / 2;
                break;
            default:
                throw std::out_of_range(&"unknown position "[line[i]]);
            }
        }
        if (row_range.first != row_range.last or col_range.first != col_range.last)
        {
            std::cout << "ERROR in ranges" << std::endl;
            return EXIT_FAILURE;
        }
        seat_ids.emplace_back(row_range.first * 8 + col_range.first);
    }

    std::cout << "max seat id: " << *std::max_element(seat_ids.begin(), seat_ids.end())
              << std::endl;

    std::sort(seat_ids.begin(), seat_ids.end());
    for (size_t i = 0; i < seat_ids.size() - 1; ++i)
    {
        if ((seat_ids[i + 1] - seat_ids[i]) > 1)
        {
            std::cout << "my seat id: " << seat_ids[i] + 1 << std::endl;
            break;
        }
    }
    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
