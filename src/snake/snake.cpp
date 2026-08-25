#include "snake.hpp"

namespace snake_game
{
snake::snake(Position start)
        : positions_{start, {start.x - 1, start.y}, {start.x - 2, start.y}},
            previous_positions_(positions_)
{
        this->direction = Direction::Right;
}

void snake::change_direction(Direction new_direction)
{
    if ((this->direction == Direction::Up && new_direction != Direction::Down) ||
        (this->direction == Direction::Down && new_direction != Direction::Up) ||
        (this->direction == Direction::Left && new_direction != Direction::Right) ||
        (this->direction == Direction::Right && new_direction != Direction::Left))
    {
        this->direction = new_direction;
    }
}
void snake::move()
{
    previous_positions_ = positions_;
    Position next = head();
    if (this->direction == Direction::Up) --next.y;
    if (this->direction == Direction::Down) ++next.y;
    if (this->direction == Direction::Left) --next.x;
    if (this->direction == Direction::Right) ++next.x;
    positions_.pop_back();
    if (find(next == positions_.back())
    {
        next = previous_positions_.back();
    }

    positions_.push_front(next);
}

void snake::eat()
{
    previous_positions_.push_back(positions_.back());
    positions_.push_back(positions_.back());
}

const std::deque<Position>& snake::positions() const
{
    return positions_;
}

const std::deque<Position>& snake::previous_positions() const
{
    return previous_positions_;
}

Position snake::head() const
{
    return positions_.front();
}
}
