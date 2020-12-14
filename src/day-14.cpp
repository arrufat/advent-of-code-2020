#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

struct mask
{
    std::string value;
    size_t zeros_mask{};
    size_t ones_mask{};

    auto part1(const std::string& s, char z = '0')
    {
        zeros_mask = (1ul << 37) - 1;
        ones_mask = 0;
        std::vector<size_t> addresses;
        const auto num = std::stoul(s);
        for (size_t i = 0; i < value.size(); ++i)
        {
            const auto pos = value.size() - i - 1;
            if (value[pos] == '1')
                ones_mask += 1ul << i;
            else if (value[pos] == z)
                zeros_mask ^= 1ul << i;
        }
        return (num | ones_mask) & zeros_mask;
    }
    auto part2(const std::string& s)
    {
        std::vector<size_t> addresses{part1(s, 'X')};
        for (size_t i = 0; i < value.size(); ++i)
        {
            const auto pos = value.size() - i - 1;
            if (value[pos] == 'X')
            {
                const auto addr_size = addresses.size();
                for (size_t j = 0; j < addr_size; ++j)
                {
                    addresses.push_back(addresses[j] | (1ul << i));
                }
            }
        }
        return addresses;
    }
};

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-14/input");
    std::map<size_t, size_t> memory, memory_v2;
    mask m;
    std::string command, equal, value;
    while (fin >> command >> equal >> value)
    {
        if (command == "mask")
        {
            m.value = value;
        }
        else
        {
            const auto address = std::stoul(command.substr(4, command.size() - 5));
            memory[address] = m.part1(value);
            const auto addresses = m.part2(std::to_string(address));
            for (const auto& addr : addresses)
                memory_v2[addr] = std::stoul(value);
        }
    }

    const auto memory_sum = [](const auto& memory) {
        size_t sum = 0;
        for (const auto& entry : memory)
            sum += entry.second;
        return sum;
    };

    std::cout << "part1: " << memory_sum(memory) << std::endl;
    std::cout << "part2: " << memory_sum(memory_v2) << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
