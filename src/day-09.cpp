#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-09/input");
    std::vector<long> input;
    for (std::string line; std::getline(fin, line);)
        input.push_back(std::stol(line));

    auto check_range = [&](const unsigned long pos) {
        std::set<long> diffs;
        const auto target = input[pos];
        bool found = false;
        for (size_t i = pos - 25; i < pos; ++i)
        {
            long diff = target - input[i];
            if (diffs.find(input[i]) != diffs.end() and diff != input[i])
            {
                found = true;
            }
            else if (diff > 0)
            {
                diffs.insert(diff);
            }
        }
        return found;
    };

    auto part1 = [&]() {
        size_t pos = 0;
        for (size_t i = 25; i < input.size(); ++i)
        {
            if (not check_range(i))
                pos = i;
        }
        return pos;
    };

    auto part2 = [&]() {
        const auto target = input[part1()];
        std::vector<long> psums;
        std::partial_sum(input.begin(), input.end(), std::back_inserter(psums));
        for (size_t i = 0; i < input.size(); ++i)
        {
            auto sum = psums[i];
            if (sum == target)
                return input[0] + input[i];

            else if (psums[i] > target)
            {
                size_t j = 0;
                do
                {
                    sum -= input[j];
                    ++j;
                } while (sum > target);
                if (sum == target)
                {
                    const auto [min, max] =
                        std::minmax_element(input.begin() + j, input.begin() + i + 1);
                    return *min + *max;
                }
                else
                {
                    continue;
                }
            }
        }
        return 0l;
    };

    std::cout << "part1: " << input[part1()] << std::endl;
    std::cout << "part2: " << part2() << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
