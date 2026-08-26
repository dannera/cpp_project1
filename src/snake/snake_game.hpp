#pragma once
#include "snake.hpp"
#include "food.hpp"
#include "board.hpp"
#include "user_input.hpp"

namespace snake_game
{

class SnakeGame
{
private:
    int window_width;
    int window_height;
    static constexpr int cell_size = 32;
    static constexpr int board_offset_x = 64;
    static constexpr int board_offset_y = 128;
    static constexpr double update_interval = 0.2;

    Board board;
    UserInput user_input;
    Snake snake;
    Food food;
    int score = 0;
    bool game_over = false;
    double lastUpdateTime = 0.0;
    
public:
    SnakeGame(int window_width, int window_height)
             : window_width(window_width), window_height(window_height),
             board(window_width, window_height, cell_size, board_offset_x, board_offset_y),
                    snake({board.width() / 2, board.height() / 2}),
                    food(board, snake.positions())
    {
    }
    ~SnakeGame();

    SnakeGame(const SnakeGame&) = delete;
    SnakeGame& operator=(const SnakeGame&) = delete;

    void get_user_input()
    {
        this->user_input.update();
    }

    void initialize_graphics()
    {
        this->board.initialize_graphics();
    }

    void shutdown_graphics()
    {
        this->board.shutdown_graphics();
    }

    bool cycle_triggered()
    {
        double current_time = GetTime();
        if (current_time - lastUpdateTime >= this->update_interval)
        {
            lastUpdateTime = current_time;
            return true;
        }
        return false;
    }

    void draw() const
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        this->board.draw(this->score);
        this->snake.draw(this->board);
        this->food.draw(this->board);
        EndDrawing();
    }

    void update()
    {
        this->snake.change_direction(user_input.direction());
        if (!this->snake.move() or this->snake.is_outside(board))
        {
            this->game_over = true;
            return;
        }
        if(this->snake.head() == this->food.position())
        {
            this->snake.eat();
            this->food.place(this->snake.positions());
            this->score++;
        }
    }
    bool is_game_over() const
    {
        return this->game_over;
    }
};


    int run();
}
