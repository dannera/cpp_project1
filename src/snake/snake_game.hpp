#pragma once
#include "snake.hpp"
#include "food.hpp"
#include "board.hpp"

namespace snake_game
{

class SnakeGame
{
private:
    static constexpr int board_width = 16;
    static constexpr int board_height = 16;
    static constexpr int cell_size = 32;

    UserInput user_input;
    Snake snake;
    Food food;
    Board board;

public:
    SnakeGame()
    {
        this->board = Board(board_width, board_height, {board_width / 2, board_height / 2});
        this->snake = Snake({board_width / 2, board_height / 2});
        this->food = Food(board_width, board_height, cell_size, snake.positions());
    }
    ~SnakeGame();

    SnakeGame(const SnakeGame&) = delete;
    SnakeGame& operator=(const SnakeGame&) = delete;

    void draw() const
    {
        this->board.draw();
        this->snake.draw();
        this->food.draw();
    }

    void update()
    {
        
        this->snake.change_direction(user_input.direction());
        if (!this->snake.move() or !this->board.inside(this->snake.head()))
        {
            this->game_over();   // Handle game over logic
            return;
        }
        if(this->snake.head() == this->food.position())
        {
            this->snake.eat();
            this->food.place(this->snake.positions());
        }
        this->board.update();
    }
    void game_over()
    {
        // Handle game over logic, e.g., display a message, reset the game, etc.
    }
};


    int run();
}
