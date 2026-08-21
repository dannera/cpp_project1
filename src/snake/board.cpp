#include "board.hpp"

#include <algorithm>
#include <iostream>
#include <string>

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
    std::cout << "\033[H\033[2J";
    std::cout << "Snake   Score: " << score << "\n";
    std::cout << '+' << std::string(width_, '-') << "+\n";

    const auto& positions = snake_.positions();
    for (int y = 0; y < height_; ++y)
    {
        std::cout << '|';
        for (int x = 0; x < width_; ++x)
        {
            Position cell{x, y};
            char symbol = ' ';
            if (cell == positions.front())
                symbol = '@';
            else if (std::find(positions.begin() + 1, positions.end(), cell) != positions.end())
                symbol = 'o';
            else if (cell == food_)
                symbol = '*';
            std::cout << symbol;
        }
        std::cout << "|\n";
    }
    std::cout << '+' << std::string(width_, '-') << "+\n";
    std::cout << "Arrow keys to move, Q to quit" << std::flush;
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
