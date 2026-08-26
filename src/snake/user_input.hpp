#pragma once

#include "snake_types.hpp"

#include <raylib.h>
#include <iostream>

namespace snake_game
{
class UserInput
{
private:

    Direction requested_direction = Direction::Right;

public:
    UserInput() = default;
    UserInput(const UserInput&) = delete;
    UserInput& operator=(const UserInput&) = delete;

    void update()
    {
        if (IsKeyPressed(KEY_UP)) this->requested_direction = Direction::Up;
        if (IsKeyPressed(KEY_DOWN)) this->requested_direction = Direction::Down;
        if (IsKeyPressed(KEY_LEFT)) this->requested_direction = Direction::Left;
        if (IsKeyPressed(KEY_RIGHT)) this->requested_direction = Direction::Right;
    }
    Direction direction()
    {
        return this->requested_direction;
    }

};
}