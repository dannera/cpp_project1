#pragma once

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

    void move(Direction direction);
    void eat();

    const std::deque<Position>& positions() const;
    Position head() const;

private:
    std::deque<Position> positions_;
};
}
