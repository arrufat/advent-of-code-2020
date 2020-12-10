#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-10/input");
    std::vector<int> input;
    for (std::string line; std::getline(fin, line);)
        input.push_back(std::stoi(line));

    auto part1 = [&]() {
        std::sort(input.begin(), input.end());
        std::vector<int> diffs(input.size());
        std::adjacent_difference(input.begin(), input.end(), diffs.begin());
        const auto num1 = std::count(diffs.begin(), diffs.end(), 1);
        const auto num3 = std::count(diffs.begin(), diffs.end(), 3) + 1;
        return std::pair(num1, num3);
    };

    auto part2 = [&]() {
        input.push_back(0);
        std::sort(input.begin(), input.end());
        // table of combinations up to each point
        std::unordered_map<int, long> cache;
        cache[input.back() + 3] = 1;  // add the last adapter
        for (auto it = input.rbegin(); it != input.rend(); ++it)
        {
            cache[*it] = cache[*it + 1] + cache[*it + 2] + cache[*it + 3];
        }
        return cache[0];
    };

    const auto [num1, num3] = part1();
    std::cout << "part1: " << num1 * num3 << std::endl;
    std::cout << "part2: " << part2() << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
