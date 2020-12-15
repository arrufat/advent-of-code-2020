#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    const std::vector<int> numbers{1, 0, 18, 10, 19, 6};

    const auto solve = [&](size_t iterations) {
        std::unordered_map<int, int> state;
        for (size_t i{}; const auto n : numbers)
            state[n] = i++;

        int prev = numbers.back();
        for (size_t i{numbers.size()}; i < iterations; ++i)
        {
            // it->first = prev, it->second = last_seen
            auto it = state.find(prev);
            if (it == state.end())
            {
                state.emplace(prev, i - 1);
                prev = 0;
            }
            else
            {
                prev = i - 1 - it->second;
                it->second = i - 1;
            }
        }
        return prev;
    };

    std::cout << "part1: " << solve(2020) << std::endl;
    std::cout << "part2: " << solve(30'000'000) << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
