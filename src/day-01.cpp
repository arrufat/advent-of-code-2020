#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-01/input");
    std::vector<int> expenses;
    for (std::string line; std::getline(fin, line);)
        expenses.push_back(std::stoi(line));

    std::unordered_map<int, int> ht;
    const int target = 2020;
    std::cout << expenses.size() << std::endl;
    // part 1
    for (size_t i = 0; const auto& expense : expenses)
    {
        int complement = target - expense;
        if (ht.find(complement) != ht.end())
        {
            std::cout << "sum:  " << expenses[i] + expenses[ht.at(complement)] << std::endl;
            std::cout << "prod: " << expenses[i] * expenses[ht.at(complement)] << std::endl;
            break;
        }
        ht[expenses[i]] = i;
        ++i;
    }
    // part 2

    std::sort(expenses.begin(), expenses.end());
    for (size_t i = 0; i < expenses.size() - 2; ++i)
    {
        int l = i + 1;
        int r = expenses.size() - 1;
        while (l < r)
        {
            if (expenses[i] + expenses[l] + expenses[r] == target)
            {
                std::cout << "sum:  " << expenses[i] + expenses[l] + expenses[r] << std::endl;
                std::cout << "prod: " << expenses[i] * expenses[l] * expenses[r] << std::endl;
                return 0;
            }
            else if (expenses[i] + expenses[l] + expenses[r] < target)
                ++l;
            else
                --r;
        }
    }

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
