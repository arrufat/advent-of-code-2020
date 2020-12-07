#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using rules_type = std::unordered_map<std::string, std::vector<std::pair<int, std::string>>>;

size_t count_bags(rules_type& rules, const std::string& b)
{
    size_t total = 0;
    for (const auto [count, bag] : rules[b])
    {
        total += count * count_bags(rules, bag) + count;
    }
    return total;
}

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-07/input");
    std::vector<std::string> input;
    for (std::string line; std::getline(fin, line);)
        input.push_back(line);

    rules_type rules;
    for (const auto& line : input)
    {
        std::istringstream sin(line);
        std::vector<std::string> words;
        std::copy(
            std::istream_iterator<std::string>(sin),
            std::istream_iterator<std::string>(),
            std::back_inserter(words));
        if (words[4] == "no")
        {
            rules[words[0] + words[1]].emplace_back(0, "");
            continue;
        }

        const auto num_bags = (words.size() - 4) / 4;

        for (size_t i = 1; i <= num_bags; ++i)
        {
            rules[words[0] + words[1]].emplace_back(
                std::stoi(words[i * 4]),
                words[i * 4 + 1] + words[i * 4 + 2]);
        }
    }

    size_t num_colors = 0;
    std::set<std::string> candidates;
    std::set<std::string> seen;
    auto count_colors = [&](const std::string& c) {
        for (const auto& [bag, contents] : rules)
        {
            for (const auto& content : contents)
            {
                if (content.second == c and seen.count(bag) == 0)
                {
                    candidates.insert(bag);
                    seen.insert(bag);
                    num_colors++;
                }
            }
        }
    };

    // initialize candidates with bags that contain shiny gold
    count_colors("shinygold");
    while (not candidates.empty())
    {
        const auto color = *candidates.begin();
        count_colors(color);
        candidates.erase(candidates.find(color));
    }
    // part 1
    std::cout << "num_colors: " << num_colors << std::endl;
    // part 2
    std::cout << count_bags(rules, "shinygold") << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
