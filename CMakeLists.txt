cmake_minimum_required(VERSION 3.17)
set(PROJECT matrix)
project(${PROJECT})

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
include_directories(src)

add_executable(${PROJECT} main.cpp)

target_link_libraries(${PROJECT} PRIVATE ncursesw)

