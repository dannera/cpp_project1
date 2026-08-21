cmake_minimum_required(VERSION 3.25)

project(MyProject)

set(CMAKE_CXX_STANDARD 23)

add_executable(
    my_app
    src/main.cpp
    src/snake/snake_game.cpp
)