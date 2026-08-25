#pragma once

#include "snake.hpp"

#include <raylib.h>

#include <random>

namespace snake_game
{
class Board
{
public:
    Board(int width, int height, Position snake_start);
    ~Board();

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    bool collides() const;
    void place_food();
    void initialize_graphics(int window_width, int window_height);
    void shutdown_graphics();
    void draw(int score, float interpolation) const;

    snake& player_snake();
    Food food();

private:
    int width_;
    int height_;
    snake snake_;
    Position food_;
    std::mt19937 random_;
    RenderTexture2D static_layer_{};
};
}
