#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class direction
{
    east = 0,
    south,
    west,
    north,
};

struct position
{
    position() = default;
    position(int x, int y, direction dir) : x(x), y(y), dir(dir) {}
    int x = 0;
    int y = 0;
    direction dir = direction::east;
    auto manhattan() { return std::abs(x) + std::abs(y); }

    auto update(const std::pair<char, int>& action)
    {
        int k = action.second / 90;
        int cur = static_cast<int>(dir);
        switch (action.first)
        {
        case 'N':
            y += action.second;
            break;
        case 'S':
            y -= action.second;
            break;
        case 'E':
            x += action.second;
            break;
        case 'W':
            x -= action.second;
            break;
        case 'L':
            dir = static_cast<direction>((cur + 3 * k) % 4);
            break;
        case 'R':
            dir = static_cast<direction>((cur + k) % 4);
            break;
        case 'F':
            if (dir == direction::east)
                x += action.second;
            else if (dir == direction::west)
                x -= action.second;
            else if (dir == direction::north)
                y += action.second;
            else if (dir == direction::south)
                y -= action.second;
            break;
        default:
            break;
        }
    }
    auto print()
    {
        const std::string dirs{"ESWN"};
        std::cout << dirs[static_cast<int>(dir)] << ": " << x << ", " << y << std::endl;
    }
};

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-12/input");
    std::vector<std::pair<char, int>> actions;
    for (std::string line; std::getline(fin, line);)
    {
        std::istringstream sout(line);
        std::pair<char, int> action;
        sout >> action.first >> action.second;
        actions.push_back(std::move(action));
    }

    position pos;
    for (const auto& action : actions)
    {
        pos.update(action);
    }
    std::cout << "part1: " << pos.manhattan() << std::endl;

    auto part2 = [&]() {
        std::pair<int, int> waypoint(10, 1);
        std::pair<int, int> position(0, 0);
        float angle;
        float rot_x, rot_y;
        for (const auto& action : actions)
        {
            switch (action.first)
            {
            case 'N':
                waypoint.second += action.second;
                break;
            case 'S':
                waypoint.second -= action.second;
                break;
            case 'E':
                waypoint.first += action.second;
                break;
            case 'W':
                waypoint.first -= action.second;
                break;
            case 'L':
            case 'R':
                angle = action.second * M_PI / 180.0;
                if (action.first == 'R')
                    angle *= -1;
                rot_x = std::round(waypoint.first * cos(angle) - waypoint.second * sin(angle));
                rot_y = std::round(waypoint.first * sin(angle) + waypoint.second * cos(angle));
                waypoint.first = rot_x;
                waypoint.second = rot_y;
                break;
            case 'F':
                position.first += waypoint.first * action.second;
                position.second += waypoint.second * action.second;
                break;
            default:
                break;
            }
        }
        return std::abs(position.first) + std::abs(position.second);
    };
    std::cout << "part2: " << part2() << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
