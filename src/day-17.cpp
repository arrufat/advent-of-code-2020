#include <fstream>
#include <iostream>
#include <set>
#include <vector>

// shamelessly stolen from https://github.com/ruippeixotog/advent-of-code/blob/master/2020/day17.cpp
auto fill_cube(std::vector<std::vector<int>>& cube, std::vector<int>& pos, int k = 0)
{
    if (k == pos.size())
    {
        cube.push_back(pos);
        return;
    }
    int base = pos[k];
    for (int d = -1; d <= 1; ++d)
    {
        pos[k] = base + d;
        fill_cube(cube, pos, k + 1);
    }
    pos[k] = base;
}

int solve(std::set<std::vector<int>>& grid, int iterations)
{
    for (int k = 0; k < iterations; ++k)
    {
        std::set<std::vector<int>> new_grid, positions;
        for (auto base_pos : grid)
        {
            std::vector<std::vector<int>> cube;
            fill_cube(cube, base_pos);
            positions.insert(cube.begin(), cube.end());
        }
        for (auto pos : positions)
        {
            std::vector<std::vector<int>> adjs;
            fill_cube(adjs, pos);
            int active_adjs = 0;
            for (auto adj : adjs)
            {
                if (adj != pos and grid.count(adj))
                    ++active_adjs;
            }
            if (active_adjs == 3 or (active_adjs == 2 and grid.count(pos)))
                new_grid.emplace(pos);
        }
        grid = new_grid;
    }
    return grid.size();
}

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-17/input");
    std::vector<std::string> input;
    std::string line;
    std::set<std::vector<int>> grid_3d, grid_4d;
    for (int i{}; std::getline(fin, line); ++i)
    {
        for (int j{}; j < line.size(); ++j)
        {
            if (line[j] == '#')
            {
                grid_3d.insert({i, j, 0});
                grid_4d.insert({i, j, 0, 0});
            }
        }
    }

    std::cout << "part1: " << solve(grid_3d, 6) << std::endl;
    std::cout << "part2: " << solve(grid_4d, 6) << std::endl;
    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
