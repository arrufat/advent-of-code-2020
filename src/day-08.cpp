#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-08/input");
    std::vector<std::string> input;
    for (std::string line; std::getline(fin, line);)
        input.push_back(line);

    auto part1 = [](const std::vector<std::string>& instructions) {
        int acc = 0;
        size_t pos = 0;
        std::vector<int> execs(instructions.size(), 0);
        do
        {
            std::istringstream sin(instructions[pos]);
            std::string instruction;
            int val;
            sin >> instruction >> val;
            execs[pos] += 1;
            if (std::any_of(execs.begin(), execs.end(), [](int i) { return i > 1; }))
            {
                break;
            }
            if (instruction == "acc")
            {
                acc += val;
                ++pos;
            }
            else if (instruction == "jmp")
            {
                pos += val;
            }
            else if (instruction == "nop")
            {
                ++pos;
            }
        } while (pos < instructions.size());
        return std::make_pair(pos, acc);
    };

    auto part2 = [&]()
    {
        for (size_t i = 0; i < input.size(); ++i)
        {
            std::istringstream sin(input[i]);
            std::string instruction;
            int val;
            sin >> instruction >> val;
            if (instruction == "acc")
                continue;
            auto instructions = input;
            if (instruction == "jmp")
                instructions[i] = "nop " + std::to_string(val);
            else
                instructions[i] = "jmp " + std::to_string(val);
            auto out = part1(instructions);
            if (out.first == instructions.size())
            {
                return out.second;
            }
        }
        return -1;
    };

    std::cout << "part1: " << part1(input).second << std::endl;
    std::cout << "part2: " << part2() << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
