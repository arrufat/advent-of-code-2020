#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    struct password_debug
    {
        int min = std::numeric_limits<int>::max();
        int max = -1;
        char c{};
        std::string password{};

        auto check_part1() const -> bool
        {
            auto counts = std::count(password.begin(), password.end(), c);
            if (min <= counts and counts <= max)
                return true;
            else
                return false;
        }

        auto check_part2() const -> bool
        {
            if ((password[min - 1] == c and password[max - 1] != c) or
                (password[min - 1] != c and password[max - 1] == c))
                return true;
            else
                return false;
        }
    };

    std::vector<password_debug> passwords;
    std::ifstream fin("data/day-02/input");
    for (std::string line; std::getline(fin, line);)
    {
        int min, max;
        char c, discard;
        std::string password;
        std::istringstream sin(line);
        password_debug pwd;
        sin >> pwd.min >> pwd.max >> pwd.c >> discard >> pwd.password;
        pwd.max = std::abs(pwd.max);
        passwords.push_back(std::move(pwd));
    }

    auto part1 = [&]() {
        auto counts = std::count_if(passwords.begin(), passwords.end(), [](const auto& p) {
            return p.check_part1();
        });
        std::cout << counts << std::endl;
    };

    auto part2 = [&]() {
        auto counts = std::count_if(passwords.begin(), passwords.end(), [](const auto& p) {
            return p.check_part2();
        });
        std::cout << counts << std::endl;
    };

    part1();
    part2();
    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
