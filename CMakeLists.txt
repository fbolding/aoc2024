# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name and the languages used
project(AoC2024)

# Add the util folder as a subdirectory (this compiles the utility code into a library)
add_subdirectory(util)

# Add subdirectories for each day's challenge (e.g., day8, day9, etc.)
add_subdirectory(day8)
add_subdirectory(day9)
add_subdirectory(day10)
add_subdirectory(day11)
add_subdirectory(day12)