#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

auto eval_rules_part1(const std::string& line) -> long
{
    auto i = line.find(' ') + 1;
    long result = std::stol(line.substr(0, i));
    int j;
    while (i < line.size())
    {
        auto op = line[i];
        i += 2;
        j = i;
        while (j < line.size() and line[j] != ' ')
        {
            ++j;
        }
        auto arg = std::stol(line.substr(i, j - i));
        if (op == '+')
            result += arg;
        else
            result *= arg;
        i = j + 1;
    }
    return result;
}

auto eval_rules_part2(std::string line)
{
    int plus = line.find('+');
    int idx_one, idx_two;
    while (plus != std::string::npos)
    {
        long sum = 0;
        for (int i = plus - 2; i >= -1; --i)
        {
            if (i == -1 or line[i] == ' ')
            {
                sum += std::stol(line.substr(i + 1, plus - i - 2));
                idx_one = i + 1;
                break;
            }
        }
        for (int i = plus + 2; i <= line.size(); ++i)
        {
            if (i == line.size() or line[i] == ' ')
            {
                sum += std::stol(line.substr(plus + 2, i - plus - 2));
                idx_two = i;
                break;
            }
        }
        line = line.substr(0, idx_one) + std::to_string(sum) + line.substr(idx_two);
        plus = line.find('+');
    }
    auto i = line.find(' ');
    long result = std::stol(line.substr(0, i));
    i += 3;
    while (i < line.size())
    {
        int j = i;
        while (j < line.size() and line[j] != ' ')
        {
            ++j;
        }
        auto arg = std::stol(line.substr(i, j - i));
        result *= arg;
        i = j + 3;
    }
    return result;
}

template <typename function> auto solve(const std::string& input, function rules) -> long
{
    long sum = 0;
    std::string sub_expr;
    long result_sub_expr = 0;
    int close_paren = 0, open_paren = 0;
    std::ifstream fin(input);
    for (std::string line; std::getline(fin, line);)
    {
        while (true)
        {
            close_paren = line.find(')');
            if (close_paren == std::string::npos)
            {
                sum += rules(line);
                break;
            }
            open_paren = line.rfind('(', close_paren);
            sub_expr = line.substr(open_paren + 1, close_paren - open_paren - 1);
            result_sub_expr = rules(sub_expr);
            line = line.substr(0, open_paren) + std::to_string(result_sub_expr) +
                   line.substr(close_paren + 1);
        }
    }
    return sum;
}

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::cout << "part1: " << solve("data/day-18/input", eval_rules_part1)<< std::endl;
    std::cout << "part2: " << solve("data/day-18/input", eval_rules_part2)<< std::endl;
    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
