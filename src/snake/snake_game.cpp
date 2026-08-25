#include "snake_game.hpp"

#include "board.hpp"

#include <raylib.h>

#include <cstdlib>
#include <iostream>

namespace snake_game
{
namespace
{
constexpr int board_width = 30;
constexpr int board_height = 16;

bool is_opposite(Direction first, Direction second)
{
    return (first == Direction::Up && second == Direction::Down) ||
           (first == Direction::Down && second == Direction::Up) ||
           (first == Direction::Left && second == Direction::Right) ||
           (first == Direction::Right && second == Direction::Left);
}

Direction read_direction(Direction current)
{
    Direction requested = current;
    if (IsKeyPressed(KEY_UP)) requested = Direction::Up;
    if (IsKeyPressed(KEY_DOWN)) requested = Direction::Down;
    if (IsKeyPressed(KEY_LEFT)) requested = Direction::Left;
    if (IsKeyPressed(KEY_RIGHT)) requested = Direction::Right;
    return is_opposite(current, requested) ? current : requested;
}
}

int run()
{
    constexpr int cell_size = 32;
    constexpr int window_width = board_width * cell_size + 64;
    constexpr int window_height = board_height * cell_size + 144;
    Board board(board_width, board_height, {board_width / 2, board_height / 2});
    Direction direction = Direction::Right;
    int score = 0;
    bool game_over = false;
    float movement_timer = 0.0F;

    InitWindow(window_width, window_height, "Snake");
    SetTargetFPS(60);

    while (!WindowShouldClose() && !game_over)
    {
        direction = read_direction(direction);
        if (IsKeyPressed(KEY_ESCAPE)) break;

        movement_timer += GetFrameTime();
        if (movement_timer >= 0.12F)
        {
            movement_timer = 0.0F;
            board.player_snake().move(direction);

            if (board.collides())
            {
                game_over = true;
                continue;
            }

            if (board.player_snake().head() == board.food())
            {
                board.player_snake().eat();
                ++score;
                board.place_food();
            }
        }

        board.draw(score);
    }

    CloseWindow();
    return EXIT_SUCCESS;
}
}
