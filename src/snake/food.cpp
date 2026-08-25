#include "food.hpp"

namespace snake_game
{
Food::Food(int board_width, int board_height, int cell_size, const std::deque<Position>& snake_positions)
    : width_(board_width), height_(board_height), cell_size_(cell_size), random_(std::random_device{}())
{
    place(snake_positions);
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

void Food::draw() const
{
    DrawRectangle(this->position_.x * this->cell_size,
                  this->position_.y * this->cell_size,
                  this->cell_size, this->cell_size, this->food_color);
}
}