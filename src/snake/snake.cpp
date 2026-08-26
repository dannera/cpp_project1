#include "snake.hpp"

#include <algorithm>

namespace snake_game
{
Snake::Snake(Position start)
        : positions_{start, {start.x - 1, start.y}, {start.x - 2, start.y}}
{
        this->direction = Direction::Right;
}

void Snake::change_direction(Direction new_direction)
{
    if ((this->direction == Direction::Up && new_direction != Direction::Down) ||
        (this->direction == Direction::Down && new_direction != Direction::Up) ||
        (this->direction == Direction::Left && new_direction != Direction::Right) ||
        (this->direction == Direction::Right && new_direction != Direction::Left))
    {
        this->direction = new_direction;
    }
}
bool Snake::move()
{
    Position next = head();
    if (this->direction == Direction::Up) --next.y;
    if (this->direction == Direction::Down) ++next.y;
    if (this->direction == Direction::Left) --next.x;
    if (this->direction == Direction::Right) ++next.x;
    positions_.pop_back();
    if (std::find(positions_.begin(), positions_.end(), next) != positions_.end())
    {
        return false;
    }

    positions_.push_front(next);
    return true;
}

void Snake::draw(const Board& board) const
{   
    bool is_head_position = true;
    for (const Position& segment : positions_)
    {
        const Color color = is_head_position ? this->head_color : this->body_color;
        is_head_position = false;
        DrawRectangle(board.offset_x + segment.x * board.cell_size + 2,
                      board.offset_y + segment.y * board.cell_size + 2,
                      board.cell_size - 4, board.cell_size - 4, color);
    }
}

void Snake::eat()
{
    positions_.push_back(positions_.back());
}
bool Snake::is_outside(const Board& board) const
{
    const Position head_position = head();
    return head_position.x < 0 || head_position.x >= board.width() ||
           head_position.y < 0 || head_position.y >= board.height();
}
const std::deque<Position>& Snake::positions() const
{
    return positions_;
}

Position Snake::head() const
{
    return positions_.front();
}
}
