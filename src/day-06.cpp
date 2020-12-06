#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-06/input");
    std::vector<std::string> input;
    for (std::string line; std::getline(fin, line);)
        input.push_back(line);

    // // clang-format off
    // input =
    // {
    //     "abc",
    //     "",
    //     "a",
    //     "b",
    //     "c",
    //     "",
    //     "ab",
    //     "ac",
    //     "",
    //     "a",
    //     "a",
    //     "a",
    //     "a",
    //     "",
    //     "b",
    // };
    // // clang-format on

    auto part1 = [&]() {
        std::vector<std::set<char>> ans(1);
        size_t group_id = 0;
        for (const auto& line : input)
        {
            if (line.empty())
            {
                ans.push_back(std::set<char>());
                ++group_id;
            }
            else
            {
                for (const auto c : line)
                    ans[group_id].insert(c);
            }
        }

        size_t num_yes = 0;
        for (const auto& s : ans)
            num_yes += s.size();
        std::cout << "part1: " << num_yes << std::endl;
    };

    auto part2 = [&]() {
        std::vector<std::unordered_map<char, int>> ans(1);
        size_t group_id = 0;
        std::vector<int> members(1, 0);
        for (const auto& line : input)
        {
            if (line.empty())
            {
                ans.push_back(std::unordered_map<char, int>());
                members.push_back(0);
                ++group_id;
            }
            else
            {
                for (const auto c : line)
                    ans[group_id][c]++;
                members[group_id]++;
            }
        }
        size_t num_yes = 0;
        for (size_t i = 0; i < ans.size(); ++i)
        {
            for (const auto& [a, count] : ans[i])
            {
                if (count == members[i])
                    ++num_yes;
            }
        }
        std::cout << "part2: " << num_yes << std::endl;
    };

    part1();
    part2();

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
