cmake_minimum_required(VERSION 3.14)
project("Advent of Code 2020" LANGUAGES CXX)

# Use C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Colored warnings
option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." ON)
if(${FORCE_COLORED_OUTPUT})
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        add_compile_options (-fdiagnostics-color=always)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options (-fcolor-diagnostics)
    endif()
endif()

# Enable ccache if it exists
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif (CCACHE_FOUND)

# Optimization flags
include(CheckCXXCompilerFlag)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
    if(COMPILER_SUPPORTS_MARCH_NATIVE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif()
endif()

macro(add_day number)
    add_executable(day-${number} src/day-${number}.cpp)
endmacro()

add_day(01)
add_day(02)
add_day(03)
add_day(04)
add_day(05)
add_day(06)
add_day(07)
add_day(08)
add_day(09)
add_day(10)
add_day(11)
add_day(12)
add_day(13)
