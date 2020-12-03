#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-03/input");
    std::vector<std::string> geology;
    for (std::string line; std::getline(fin, line);)
        geology.push_back(line);

    auto part1 = [&]() {
        size_t num_trees{};
        for (size_t i = 0; const auto& line : geology)
        {
            const auto pos = (3 * i) % line.length();
            if (line.at(pos) == '#')
                ++num_trees;
            ++i;
        }
        std::cout << "number of trees: " << num_trees << std::endl;
    };

    auto part2 = [&]() {
        std::vector<size_t> num_trees(5, 0);
        for (auto i = 0; const auto& line : geology)
        {
            const auto pos_11 = (1 * i) % line.length();
            const auto pos_13 = (3 * i) % line.length();
            const auto pos_15 = (5 * i) % line.length();
            const auto pos_17 = (7 * i) % line.length();
            for (auto n = 0; const auto& pos : {pos_11, pos_13, pos_15, pos_17})
            {
                if (line.at(pos) == '#')
                {
                    num_trees.at(n)++;
                }
                ++n;
            }
            if (i % 2 == 0)
            {
                const auto pos = (i / 2) % line.length();
                if (line.at(pos) == '#')
                    num_trees.at(4)++;
            }
            ++i;
        }
        std::cout
            << "product of trees: "
            << std::accumulate(num_trees.begin(), num_trees.end(), 1, std::multiplies<size_t>())
            << std::endl;
    };

    part1();
    part2();
    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
