#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::vector<int> numbers{1, 0, 18, 10, 19, 6};
    // std::vector<int> numbers{0, 3, 6};

    std::unordered_map<int, int> state;
    for (size_t i{}; const auto n : numbers)
        state[n] = i++;

    const auto solve = [&](size_t last) {
        int prev = numbers.back();
        for (size_t i{numbers.size()}; i < last; ++i)
        {
            if (state.find(prev) == state.end())
            {
                state[prev] = i - 1;
                prev = 0;
            }
            else
            {
                auto& last_seen = state.at(prev);
                prev = i - 1 - last_seen;
                last_seen = i - 1;
            }
            numbers.push_back(prev);
        }
        return numbers.back();
    };

    std::cout << "part1: " << solve(2020) << std::endl;
    std::cout << "part2: " << solve(30'000'000) << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
