#pragma once

#include <raylib.h>

#include "snake_types.hpp"
#include <random>

namespace snake_game
{

class Board
{
public:
    Board(int width, int height, int cell_size = 32, int offset_x = 32, int offset_y = 96);
    ~Board();

    static constexpr Color background_color{18, 25, 38, 255};
    static constexpr Color board_color{30, 41, 59, 255};
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    
    int cell_size;
    int offset_x;
    int offset_y;
    void initialize_graphics();
    void shutdown_graphics();
    void draw(int score) const;
    int width() const;
    int height() const;

private:
    int window_width_;
    int window_height_;
    int width_;
    int height_;
    RenderTexture2D static_layer_{};
};
}
