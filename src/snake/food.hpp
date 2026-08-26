#pragma once

#include "board.hpp"
#include "snake_types.hpp"
#include <deque>
namespace snake_game
{


class Food
{
public:
    Food(const Board& board, const std::deque<Position>& snake_positions);
    Position position() const;
    void place(const std::deque<Position>& snake_positions);
    void draw(const Board& board) const;
private:
    int width_;
    int height_;
    int cell_size_;
    Position position_;
    std::mt19937 random_;
    static constexpr Color food_color{251, 113, 133, 255};

};
}