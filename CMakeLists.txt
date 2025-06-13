cmake_minimum_required(VERSION 3.10)
project(Rasterizer C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -Wall -Wextra -Wpedantic -Werror -O3 -fopenmp")

# Add subdirectories
add_subdirectory(lib)
add_subdirectory(app)

