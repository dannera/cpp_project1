#include "snake.hpp"

namespace snake_game
{
snake::snake(Position start)
    : positions_{start, {start.x - 1, start.y}, {start.x - 2, start.y}}
{
}

void snake::move(Direction direction)
{
    Position next = head();
    if (direction == Direction::Up) --next.y;
    if (direction == Direction::Down) ++next.y;
    if (direction == Direction::Left) --next.x;
    if (direction == Direction::Right) ++next.x;

    positions_.push_front(next);
    positions_.pop_back();
}

void snake::eat()
{
    positions_.push_back(positions_.back());
}

const std::deque<Position>& snake::positions() const
{
    return positions_;
}

Position snake::head() const
{
    return positions_.front();
}
}
