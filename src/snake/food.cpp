#include "food.hpp"

#include <algorithm>

namespace snake_game
{
Food::Food(const Board& board, const std::deque<Position>& snake_positions)
    : width_(board.width()), height_(board.height()), cell_size_(board.cell_size), random_(std::random_device{}())
{
    place(snake_positions);
}

Position Food::position() const
{
    return position_;
}

void Food::place(const std::deque<Position>& snake_positions)
{
    std::uniform_int_distribution<int> x_distribution(0, this->width_ - 1);
    std::uniform_int_distribution<int> y_distribution(0, this->height_ - 1);
    do
    {
        this->position_ = {x_distribution(this->random_), y_distribution(this->random_)};
    } while (std::find(snake_positions.begin(), snake_positions.end(), this->position_) != snake_positions.end());
}

void Food::draw(const Board& board) const
{
    DrawRectangle(board.offset_x + this->position_.x * board.cell_size,
                  board.offset_y + this->position_.y * board.cell_size,
                  board.cell_size, board.cell_size, this->food_color);
}
}