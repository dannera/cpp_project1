#include "board.hpp"

#include <raylib.h>

#include <algorithm>

namespace snake_game
{
Board::Board(int width, int height, Position snake_start)
    : width_(width), height_(height), snake_(snake_start), food_{5, 5}, random_(std::random_device{}())
{
}

Board::~Board()
{
    shutdown_graphics();
}

void Board::shutdown_graphics()
{
    if (static_layer_.id != 0)
    {
        UnloadRenderTexture(static_layer_);
        static_layer_ = {};
    }
}

bool Board::inside(const Position& position) const
{
    const bool inside_board = position.x < 0 || position.x >= width_ || position.y < 0 || position.y >= height_;
    return hits_barrier;
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

void Board::initialize_graphics(int window_width, int window_height)
{
    constexpr int cell_size = 32;
    constexpr int board_offset_x = 32;
    constexpr int board_offset_y = 96;
    const Color background{18, 25, 38, 255};
    const Color board_color{30, 41, 59, 255};

    static_layer_ = LoadRenderTexture(window_width, window_height);
    BeginTextureMode(static_layer_);
    ClearBackground(background);
    DrawText("SNAKE", board_offset_x, 24, 32, RAYWHITE);
    DrawRectangle(board_offset_x - 8, board_offset_y - 8,
                  width_ * cell_size + 16, height_ * cell_size + 16, board_color);
    DrawRectangle(board_offset_x, board_offset_y,
                  width_ * cell_size, height_ * cell_size, Color{15, 23, 42, 255});
    DrawText("ARROW KEYS  MOVE     ESC  QUIT", board_offset_x, board_offset_y + height_ * cell_size + 24,
             16, Color{148, 163, 184, 255});
    EndTextureMode();
}

void Board::draw(int score, float interpolation) const
{
    constexpr int cell_size = 32;
    constexpr int board_offset_x = 32;
    constexpr int board_offset_y = 96;
    const Color snake_color{74, 222, 128, 255};
    const Color head_color{134, 239, 172, 255};
    const Color food_color{251, 113, 133, 255};

    BeginDrawing();
    DrawTextureRec(static_layer_.texture,
                   Rectangle{0, 0, static_cast<float>(static_layer_.texture.width),
                              -static_cast<float>(static_layer_.texture.height)},
                   Vector2{0, 0}, WHITE);
    DrawText(TextFormat("SCORE  %d", score), board_offset_x, 62, 20, Color{148, 163, 184, 255});

    const auto& positions = snake_.positions();
    const auto& previous_positions = snake_.previous_positions();
    for (std::size_t index = 0; index < positions.size(); ++index)
    {
        const Position previous = previous_positions[index];
        const Position current = positions[index];
        const float x = static_cast<float>(previous.x) +
                        static_cast<float>(current.x - previous.x) * interpolation;
        const float y = static_cast<float>(previous.y) +
                        static_cast<float>(current.y - previous.y) * interpolation;
        const Color color = index == 0 ? head_color : snake_color;
        DrawRectangle(board_offset_x + x * cell_size + 2,
                      board_offset_y + y * cell_size + 2,
                      cell_size - 4, cell_size - 4, color);
    }

    DrawCircle(board_offset_x + food_.x * cell_size + cell_size / 2,
               board_offset_y + food_.y * cell_size + cell_size / 2,
               cell_size / 3.0F, food_color);
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
