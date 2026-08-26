#include "board.hpp"

#include <raylib.h>

#include <algorithm>

namespace snake_game
{
Board::Board(int window_width, int window_height, int cell_size, int offset_x, int offset_y)
    : window_width_(window_width), window_height_(window_height), cell_size(cell_size), width_( (window_width - offset_x*2) / cell_size ), height_((window_height - offset_y*2) / cell_size), offset_x(offset_x), offset_y(offset_y)
{
}

void Board::initialize_graphics()
{
    this->static_layer_ = LoadRenderTexture(this->window_width_, this->window_height_);
    BeginTextureMode(this->static_layer_);
    ClearBackground(this->background_color);
    DrawText("SNAKE", this->offset_x, 24, 32, RAYWHITE);
    DrawRectangle(this->offset_x-this->cell_size, this->offset_y-this->cell_size,
                  this->width_ * this->cell_size + this->cell_size * 2, this->height_ * this->cell_size + this->cell_size * 2, this->board_color);
    DrawRectangle(this->offset_x, this->offset_y,
                  this->width_ * this->cell_size, this->height_ * this->cell_size, Color{15, 23, 42, 255});
    DrawText("ARROW KEYS : MOVE     ESC : QUIT", this->offset_x, this->offset_y + this->height_ * this->cell_size + this->cell_size * 2,
             16, Color{148, 163, 184, 255});
    EndTextureMode();
}

Board::~Board()
{
    shutdown_graphics();
}

void Board::shutdown_graphics()
{
    if (static_layer_.id != 0)
    {
        UnloadRenderTexture(static_layer_);
        static_layer_ = {};
    }
}

void Board::draw(int score) const
{
    DrawTextureRec(this->static_layer_.texture,
                   Rectangle{0, 0, static_cast<float>(this->static_layer_.texture.width),
                              -static_cast<float>(this->static_layer_.texture.height)},
                   Vector2{0, 0}, WHITE);
    DrawText(TextFormat("SCORE  %d", score), this->offset_x, 62, 20, Color{148, 163, 184, 255});
}

int Board::width() const
{
    return width_;
}

int Board::height() const
{
    return height_;
}

}
