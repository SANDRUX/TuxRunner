cmake_minimum_required(VERSION 3.5)

project(tux_runner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tux_runner main.cpp)

target_link_libraries(tux_runner -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio)
