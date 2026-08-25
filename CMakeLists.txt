cmake_minimum_required(VERSION 3.25)

project(MyProject)

set(CMAKE_CXX_STANDARD 23)

find_package(raylib CONFIG REQUIRED)

add_executable(
    my_app
    src/main.cpp
    src/snake/snake.cpp
    src/snake/board.cpp
    src/snake/snake_game.cpp
)

target_link_libraries(my_app PRIVATE raylib)