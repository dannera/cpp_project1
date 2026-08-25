#include "snake_game.hpp"

#include "board.hpp"
#include "food.hpp"
#include "snake.hpp"
#include <raylib.h>

#include <cstdlib>
#include <iostream>

namespace snake_game
{
namespace
{
constexpr int board_width = 16;
constexpr int board_height = 16;


int run()
{

    SnakeGame snake_game = SnakeGame();
    int score = 0;
    bool game_over = false;
    float movement_timer = 0.0F;

    InitWindow(window_width, window_height, "Snake");
    SetTargetFPS(60);
    board.initialize_graphics(window_width, window_height);

    while (!WindowShouldClose() && !game_over)
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        
        snake_game.update();
        snake_game.draw();
        EndDrawing();
        /*
        direction = read_direction(direction);
        if (IsKeyPressed(KEY_ESCAPE)) break;

        movement_timer += GetFrameTime();
        while (movement_timer >= step_duration)
        {
            movement_timer -= step_duration;
            board.player_snake().move(direction);

            if (board.collides())
            {
                game_over = true;
                break;
            }

            if (board.player_snake().head() == board.food())
            {
                board.player_snake().eat();
                ++score;
                board.place_food();
            }
        }

        board.draw(score, movement_timer / step_duration);
        */
    }

    board.shutdown_graphics();
    CloseWindow();
    return EXIT_SUCCESS;
}
}
