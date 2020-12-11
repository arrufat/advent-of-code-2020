#include <fstream>
#include <iostream>
#include <vector>

auto inbounds(int r, int c, int nr, int nc)
{
    return 0 <= r and r < nr and 0 <= c and c < nc;
}

auto adjacent(const std::vector<std::string>& map, int row, int col) -> std::string
{
    const auto nr = map.size();
    const auto nc = map[0].size();
    std::string adj;
    for (int r = row - 1; r <= row + 1; ++r)
    {
        for (int c = col - 1; c <= col + 1; ++c)
        {
            if (inbounds(r, c, nr, nc) and (r != row or c != col))
            {
                adj += map[r][c];
            }
        }
    }
    return adj;
};

auto visible(const std::vector<std::string>& map, int row, int col) -> std::string
{
    const auto nr = map.size();
    const auto nc = map[0].size();
    std::string vis;
    for (int dr = -1; dr <= 1; ++dr)
    {
        for (int dc = -1; dc <= +1; ++dc)
        {
            if (dr == 0 and dc == 0)
                continue;
            int vr = row + dr;
            int vc = col + dc;
            while (inbounds(vr, vc, nr, nc) and map[vr][vc] == '.')
            {
                vr += dr;
                vc += dc;
            }

            if (inbounds(vr, vc, nr, nc))
                vis += map[vr][vc];
        }
    }
    return vis;
}

auto occupied(const std::string& s)
{
    return std::count(s.begin(), s.end(), '#');
}

template <typename function> auto step(
    const std::vector<std::string>& prev_state,
    std::vector<std::string>& next_state,
    const int threshold,
    function policy) -> bool
{
    const auto nr = prev_state.size();
    const auto nc = prev_state[0].size();
    bool changed = false;
    for (size_t r = 0; r < nr; ++r)
    {
        for (size_t c = 0; c < nc; ++c)
        {
            const auto occ = occupied(policy(prev_state, r, c));
            if (prev_state[r][c] == 'L' and occ == 0)
            {
                next_state[r][c] = '#';
                changed = true;
            }
            else if (prev_state[r][c] == '#' and occ >= threshold)
            {
                next_state[r][c] = 'L';
                changed = true;
            }
        }
    }
    return changed;
}

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    std::ifstream fin("data/day-11/input");
    std::vector<std::string> input;
    for (std::string line; std::getline(fin, line);)
        input.push_back(line);

    const auto print_state = [](const std::vector<std::string>& seats) {
        for (const auto& row : seats)
            std::cout << row << '\n';
    };

    auto prev_state = input;
    auto next_state = input;

    const auto part1 = [&]() {
        bool changed = false;
        do
        {
            changed = step(prev_state, next_state, 4, adjacent);
            prev_state = next_state;
        } while (changed);
        size_t num_seats = 0;
        for (const auto& r : prev_state)
            num_seats += occupied(r);
        return num_seats;
    };

    const auto part2 = [&]() {
        bool changed = false;
        do
        {
            changed = step(prev_state, next_state, 5, visible);
            prev_state = next_state;
        } while (changed);
        size_t num_seats = 0;
        for (const auto& r : prev_state)
            num_seats += occupied(r);
        return num_seats;
    };

    prev_state = input;
    std::cout << "part1: " << part1() << std::endl;
    prev_state = input;
    std::cout << "part1: " << part2() << std::endl;

    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
