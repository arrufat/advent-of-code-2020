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

        auto check_fields() const -> bool
        {
            if (byr == -1 or iyr == -1 or eyr == -1 or hgt.empty() or ecl.empty() or hcl.empty() or
                pid.empty())
                return false;
            return true;
        }
        auto check_byr() const -> bool { return check_range(byr, 1920, 2002); }
        auto check_iyr() const -> bool { return check_range(iyr, 2010, 2020); }
        auto check_eyr() const -> bool { return check_range(eyr, 2020, 2030); }
        auto check_hgt() const -> bool
        {
            std::stringstream sin(hgt);
            std::string unit;
            int val;
            sin >> std::ws >> val >> unit;
            if (unit != "in" and unit != "cm")
                return false;
            if (unit == "cm" and (not check_range(val, 150, 193)))
                return false;
            if (unit == "in" and (not check_range(val, 59, 76)))
                return false;
            return true;
        }
        auto check_hcl() const -> bool
        {
            if (hcl[0] != '#' and hcl.length() != 7)
                return false;
            return std::any_of(hcl.begin() + 1, hcl.end(), [](char c) {
                return ((c >= '0' and c <= '9') or (c >= 'a' and c <= 'f'));
            });
        }
        auto check_ecl() const -> bool
        {
            const std::vector<std::string> colors{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
            if (std::find(colors.begin(), colors.end(), ecl) == colors.end())
                return false;
            return true;
        }
        auto check_pid() const -> bool
        {
            if (pid.length() != 9)
                return false;
            return std::none_of(pid.begin(), pid.end(), [](char c) {
                return (c < '0' or c > '9');
            });
        }

        private:
        auto check_range(const int val, const int min, const int max) const -> bool
        {
            if (val < min or val > max)
                return false;
            return true;
        }
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
    int valid_passports = passports.size();
    for (const auto& p : passports)
    {
        if (not p.check_fields())
        {
            --valid_passports;
        }
        else  // part 2
        {
            if (not p.check_byr())
                --valid_passports;
            else if (not p.check_iyr())
                --valid_passports;
            else if (not p.check_eyr())
                --valid_passports;
            else if (not p.check_hgt())
                --valid_passports;
            else if (not p.check_hcl())
                --valid_passports;
            else if (not p.check_ecl())
                --valid_passports;
            else if (not p.check_pid())
                --valid_passports;
        }
    }
    std::cout << "num valid passports: " << valid_passports << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
