#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-13/input");
    std::string line;
    std::getline(fin, line);
    size_t timestamp = std::stoi(line);
    std::vector<int> bus_ids;
    std::string token;
    while (std::getline(fin, token, ','))
    {
        if (token == "x")
            bus_ids.push_back(0);
        else
            bus_ids.push_back(std::stoi(token));
    }

    const auto part1 = [&]() {
        const auto max_bus_id = *std::max_element(bus_ids.begin(), bus_ids.end());
        for (auto t = timestamp; t < timestamp + max_bus_id; ++t)
        {
            for (auto b : bus_ids)
            {
                if (b != 0 and t % b == 0)
                {
                    return (t - timestamp) * b;
                }
            }
        }
        return 0ul;
    };

    const auto lcm = [](const std::vector<int>& nums) {
        size_t ans = 1;
        for (const auto n : nums)
        {
            ans = std::lcm(ans, n);
        }
        return ans;
    };

    const auto part2 = [&]() {
        // brute force approach... too slow
        // for (size_t t = 0; t < std::numeric_limits<size_t>::max(); ++t)
        // {
        //     std::vector<int> rems;
        //     for (int i = 0; i < bus_ids.size(); ++i)
        //     {
        //         if (bus_ids[i] == 0)
        //             rems.push_back(0);
        //         else
        //             rems.push_back((t + i) % bus_ids[i]);
        //     }
        //     if (std::all_of(rems.begin(), rems.end(), [](auto m) { return m == 0; }))
        //         return t;
        // }
        // return 0ul;

        std::vector<int> rems(1, 0);
        std::vector<int> nums(1, bus_ids[0]);
        for (int i = 1; i < bus_ids.size(); ++i)
        {
            if (bus_ids[i] == 0)
                continue;
            nums.push_back(bus_ids[i]);
            rems.push_back(bus_ids[i] - (i % bus_ids[i]));
        }
        size_t ans = 1;
        size_t step = 1;
        std::vector<int> lcms;
        for (int i = 0; i < nums.size(); ++i)
        {
            while (ans % nums[i] != rems[i])
                ans += step;
            lcms.push_back(nums[i]);
            step = lcm(lcms);
        }
        return ans;
    };

    std::cout << "part1: " << part1() << std::endl;
    std::cout << "part2: " << part2() << std::endl;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
