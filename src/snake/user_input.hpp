#pragma once


# include <raylib.hpp>
class UserInput
{

public:
    static Direction direction() const
    {
        if (IsKeyPressed(KEY_UP)) requested = Direction::Up;
        if (IsKeyPressed(KEY_DOWN)) requested = Direction::Down;
        if (IsKeyPressed(KEY_LEFT)) requested = Direction::Left;
        if (IsKeyPressed(KEY_RIGHT)) requested = Direction::Right;
        return requested;
    }

}