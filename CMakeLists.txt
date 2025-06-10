cmake_minimum_required(VERSION 3.10)
project(Rasterizer C)  # Add CXX here if you use C++ sources

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Set compiler explicitly (optional)
set(CMAKE_C_COMPILER gcc)

# Recursively include all directories under /header
file(GLOB_RECURSE HEADER_DIRS RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/header/*.h)
foreach(header ${HEADER_DIRS})
    get_filename_component(dir ${header} DIRECTORY)
    include_directories(${CMAKE_SOURCE_DIR}/${dir})
endforeach()

# Find OpenMP (after project()!)
find_package(OpenMP REQUIRED)

# Gather all source files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror -O3 -pg -fopenmp") 

add_executable(Rasterizer ${SOURCES})

find_package(raylib REQUIRED)

target_link_libraries(Rasterizer raylib m png OpenMP::OpenMP_C)

