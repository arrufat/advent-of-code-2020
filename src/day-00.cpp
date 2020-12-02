#include <iostream>

auto main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) -> int
try
{
    return EXIT_SUCCESS;
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}
