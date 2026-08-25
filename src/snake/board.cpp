#include "board.hpp"

#include <raylib.h>

#include <algorithm>

namespace snake_game
{
Board::Board(int width, int height, Position snake_start)
    : width_(width), height_(height), snake_(snake_start), food_{5, 5}, random_(std::random_device{}())
{
}

bool Board::collides() const
{
    const Position head = snake_.head();
    const bool hits_barrier = head.x < 0 || head.x >= width_ || head.y < 0 || head.y >= height_;
    const auto& positions = snake_.positions();
    const bool hits_self = std::find(positions.begin() + 1, positions.end(), head) != positions.end();
    return hits_barrier || hits_self;
}

void Board::place_food()
{
    std::uniform_int_distribution<int> x_distribution(0, width_ - 1);
    std::uniform_int_distribution<int> y_distribution(0, height_ - 1);
    do
    {
        food_ = {x_distribution(random_), y_distribution(random_)};
    } while (std::find(snake_.positions().begin(), snake_.positions().end(), food_) != snake_.positions().end());
}

void Board::draw(int score) const
{
    constexpr int cell_size = 32;
    constexpr int board_offset_x = 32;
    constexpr int board_offset_y = 96;
    const Color background{18, 25, 38, 255};
    const Color board_color{30, 41, 59, 255};
    const Color snake_color{74, 222, 128, 255};
    const Color head_color{134, 239, 172, 255};
    const Color food_color{251, 113, 133, 255};

    BeginDrawing();
    ClearBackground(background);
    DrawText("SNAKE", board_offset_x, 24, 32, RAYWHITE);
    DrawText(TextFormat("SCORE  %d", score), board_offset_x, 62, 20, Color{148, 163, 184, 255});
    DrawRectangle(board_offset_x - 8, board_offset_y - 8,
                  width_ * cell_size + 16, height_ * cell_size + 16, board_color);
    DrawRectangle(board_offset_x, board_offset_y,
                  width_ * cell_size, height_ * cell_size, Color{15, 23, 42, 255});

    const auto& positions = snake_.positions();
    for (std::size_t index = 0; index < positions.size(); ++index)
    {
        const Position segment = positions[index];
        const Color color = index == 0 ? head_color : snake_color;
        DrawRectangle(board_offset_x + segment.x * cell_size + 2,
                      board_offset_y + segment.y * cell_size + 2,
                      cell_size - 4, cell_size - 4, color);
    }

    DrawCircle(board_offset_x + food_.x * cell_size + cell_size / 2,
               board_offset_y + food_.y * cell_size + cell_size / 2,
               cell_size / 3.0F, food_color);
    DrawText("ARROW KEYS  MOVE     ESC  QUIT", board_offset_x, board_offset_y + height_ * cell_size + 24,
             16, Color{148, 163, 184, 255});
    EndDrawing();
}

snake& Board::player_snake()
{
    return snake_;
}

Position Board::food() const
{
    return food_;
}
}
