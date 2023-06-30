cmake_minimum_required(VERSION 3.22)
project(sudoku)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(Google_tests)
add_executable(sudoku sudoku.cpp sudoku.h main.cpp start.cpp)
set(CMAKE_EXE_LINKER_FLAGS "-static")

