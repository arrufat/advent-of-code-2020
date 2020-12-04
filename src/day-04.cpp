#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-04/input");
    std::vector<std::string> input;
    for (std::string line; std::getline(fin, line);)
        input.push_back(line);

    struct passport
    {
        int byr = -1;
        int iyr = -1;
        int eyr = -1;
        std::string hgt{};
        std::string hcl{};
        std::string ecl{};
        std::string pid{};
        std::string cid{};
    };

    std::vector<passport> passports(1);
    for (const auto& line : input)
    {
        if (not line.empty())
        {
            auto& p = passports.back();
            std::istringstream sin(line);
            std::string field;
            while (std::getline(sin >> std::ws, field, ':'))
            {
                if (field == "byr")
                    sin >> p.byr;
                else if (field == "iyr")
                    sin >> p.iyr;
                else if (field == "eyr")
                    sin >> p.eyr;
                else if (field == "hgt")
                    sin >> p.hgt;
                else if (field == "hcl")
                    sin >> p.hcl;
                else if (field == "ecl")
                    sin >> p.ecl;
                else if (field == "pid")
                    sin >> p.pid;
                else if (field == "cid")
                    sin >> p.cid;
            }
        }
        else
        {
            passports.push_back(passport());
        }
    }
    std::cout << passports.size() << std::endl;
    int valid_passports = passports.size();
    for (const auto& p : passports)
    {
        if (p.byr == -1 or p.iyr == -1 or p.eyr == -1 or p.hgt.empty() or p.ecl.empty() or
            p.hcl.empty() or p.pid.empty())
        {
            --valid_passports;
        }
        else
        {
            if (p.byr < 1920 or p.byr > 2002)
            {
                --valid_passports;
                continue;
            }
            if (p.iyr < 2010 or p.iyr > 2020)
            {
                --valid_passports;
                continue;
            }
            if (p.eyr < 2020 or p.eyr > 2030)
            {
                --valid_passports;
                continue;
            }
            // check height
            std::stringstream sin(p.hgt);
            std::string unit;
            int val;
            sin >> std::ws >> val >> unit;
            if (unit != "in" and unit != "cm")
            {
                --valid_passports;
                continue;
            }
            if (unit == "cm" and (val < 150 or val > 193))
            {
                --valid_passports;
                continue;
            }
            if (unit == "in" and (val < 59 or val > 76))
            {
                --valid_passports;
                continue;
            }
            // check hair color
            if (p.hcl[0] != '#' and p.hcl.length() != 7)
            {
                --valid_passports;
                continue;
            }
            if (std::all_of(p.hcl.begin() + 1, p.hcl.end(), [](char c) {
                if ((c >= '0' and c <= '9') or (c >= 'a' and c <= 'f'))
                    return false;
                else
                    return true;
                }))
            {
                --valid_passports;
                continue;
            }

            // check eye color
            const std::vector<std::string> colors{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
            if (std::find(colors.begin(), colors.end(), p.ecl) == colors.end())
            {
                --valid_passports;
                continue;
            }

            // check pid
            if (p.pid.length() != 9)
            {
                --valid_passports;
                continue;
            }
            if (std::all_of(p.pid.begin(), p.pid.end(), [](char c) {
                    if (c >= '0' and c <= '9')
                        return false;
                    else
                        return true;
                }))
            {
                --valid_passports;
                continue;
            }
        }
    }
    std::cout << "num valid passports: " << valid_passports << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
