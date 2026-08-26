#pragma once

#include "board.hpp"
#include "snake_types.hpp"
#include <deque>

namespace snake_game
{


class Snake
{
public:
    explicit Snake(Position start);
    static constexpr Color body_color{74, 222, 128, 255};
    static constexpr Color head_color{134, 239, 172, 255};
    bool move();
    void change_direction(Direction new_direction);
    void eat();
    void draw(const Board& board) const;
    bool is_outside(const Board& board) const;
    const std::deque<Position>& positions() const;
    Position head() const;
    
private:
    Direction direction;
    std::deque<Position> positions_;
};
}
