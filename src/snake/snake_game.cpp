#include "snake_game.hpp"

#include "board.hpp"
#include "food.hpp"
#include "snake.hpp"
#include <raylib.h>

#include <cstdlib>
#include <iostream>

namespace snake_game
{


SnakeGame::~SnakeGame() = default;

int run()
{
    int window_width = 500;
    int window_height = 500;
    InitWindow(window_width, window_height, "Snake");
    SetTargetFPS(60);
    SnakeGame snake_game = SnakeGame(window_width, window_height);
    snake_game.initialize_graphics();

    while (!WindowShouldClose() && !snake_game.is_game_over())
    {
        snake_game.get_user_input();
        if(snake_game.cycle_triggered())
        {
            snake_game.update();
        }
        snake_game.draw();
    }

    snake_game.shutdown_graphics();
    CloseWindow();
    return EXIT_SUCCESS;
}
}
