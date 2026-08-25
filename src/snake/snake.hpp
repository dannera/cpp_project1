#pragma once

#include "food.hpp"
#include <deque>

namespace snake_game
{
struct Position
{
    int x;
    int y;

    bool operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }
};

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

class snake
{
public:
    explicit snake(Position start);

    void move();
    void change_direction(Direction new_direction);
    void eat();
    const std::deque<Position>& positions() const;
    const std::deque<Position>& previous_positions() const;
    Position head() const;
    
private:
    Direction direction;
    std::deque<Position> positions_;
    std::deque<Position> previous_positions_;
};
}
