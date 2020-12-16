#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <regex>
#include <set>
#include <sstream>
#include <vector>

struct constraint
{
    constraint(const std::string& s)
    {
        auto matches = std::smatch{};
        std::regex_search(s, matches, field);
        name = matches[1];
        min.first = std::stoi(matches[2]);
        max.first = std::stoi(matches[3]);
        min.second = std::stoi(matches[4]);
        max.second = std::stoi(matches[5]);
    }
    auto check(const int val) const -> bool
    {
        return (val >= min.first and val <= max.first) or
               (val >= min.second and val <= max.second);
    }
    std::string name;
    std::pair<int, int> min{0, std::numeric_limits<int>::max()};
    std::pair<int, int> max{0, std::numeric_limits<int>::max()};
    std::regex field{"([\\w ]+): (\\d+)-(\\d+) or (\\d+)-(\\d+)"};
};

auto read_ticket(const std::string& line, const std::vector<constraint>& cs) -> std::vector<int>
{
    std::istringstream sin(line);
    int val;
    char sep;
    std::vector<int> ticket;
    for (const auto& c : cs)
    {
        sin >> val >> sep;
        ticket.push_back(val);
    }
    return ticket;
}

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-16/input");
    std::vector<std::string> input;
    std::vector<constraint> constraints;
    std::string line;
    while (std::getline(fin, line))
    {
        if (not line.empty())
            constraints.emplace_back(line);
        else
            break;
    }

    std::getline(fin, line);
    std::getline(fin, line);
    const auto myticket = read_ticket(line, constraints);
    std::getline(fin, line);

    // ticket scanning error rate
    int tser = 0;
    std::getline(fin, line);
    std::vector<std::vector<int>> tickets;
    while (std::getline(fin, line))
    {
        std::vector<int> ticket = read_ticket(line, constraints);
        bool valid = false;
        for (const auto val : ticket)
        {
            valid = std::any_of(constraints.begin(), constraints.end(), [val](const auto& c) {
                return c.check(val);
            });
            if (not valid)
            {
                tser += val;
                break;
            }
        }
        if (valid)
            tickets.push_back(ticket);
    }
    std::cout << "part1: " << tser << std::endl;

    std::vector<std::set<std::string>> fields(constraints.size());
    for (size_t c = 0; c < tickets[0].size(); ++c)
    {
        for (const auto& ct : constraints)
        {
            std::vector<int> col;
            for (size_t r = 0; r < tickets.size(); ++r)
            {
                col.push_back(tickets[r][c]);
            }
            const auto ok =
                std::all_of(col.begin(), col.end(), [&ct](int n) { return ct.check(n); });
            if (ok)
                fields[c].insert(ct.name);
        }
    }

    std::set<int> processed;
    while (std::any_of(fields.begin(), fields.end(), [](const auto& f) { return f.size() != 1; }))
    {
        for (size_t i{}; i < fields.size(); ++i)
        {
            if (fields[i].size() == 1 and not processed.contains(i))
            {
                const auto name = *fields[i].begin();
                for (size_t j{}; j < fields.size(); ++j)
                {
                    if (fields[j].size() == 1)
                        continue;
                    fields[j].erase(name);
                }
            }
        }
    }

    size_t result = 1;
    for (size_t i{}; i < fields.size(); ++i)
    {
        for (const auto& s : fields[i])
        {
            if (s.find("departure") != 0)
                continue;
            result *= myticket[i];
        }
    }
    std::cout << "part2: " << result << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
}
