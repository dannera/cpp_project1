#pragma once

#include "snake.hpp"

#include <random>

namespace snake_game
{
class Board
{
public:
    Board(int width, int height, Position snake_start);

    bool collides() const;
    void place_food();
    void draw(int score) const;

    snake& player_snake();
    Position food() const;

private:
    int width_;
    int height_;
    snake snake_;
    Position food_;
    std::mt19937 random_;
};
}
