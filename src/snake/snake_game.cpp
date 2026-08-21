#include "snake_game.hpp"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <random>
#include <string>
#include <sys/select.h>
#include <termios.h>
#include <thread>
#include <unistd.h>

namespace snake
{
namespace
{
struct Position
{
    int x;
    int y;

    bool operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }
};

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

constexpr int board_width = 30;
constexpr int board_height = 16;

class TerminalMode
{
public:
    TerminalMode()
    {
        tcgetattr(STDIN_FILENO, &original_);
        termios raw = original_;
        raw.c_lflag &= static_cast<unsigned long>(~(ICANON | ECHO));
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
        std::cout << "\033[?25l";
    }

    ~TerminalMode()
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &original_);
        std::cout << "\033[?25h\033[0m\n";
    }

    TerminalMode(const TerminalMode&) = delete;
    TerminalMode& operator=(const TerminalMode&) = delete;

private:
    termios original_{};
};

bool key_available()
{
    timeval timeout{0, 0};
    fd_set input;
    FD_ZERO(&input);
    FD_SET(STDIN_FILENO, &input);
    return select(STDIN_FILENO + 1, &input, nullptr, nullptr, &timeout) > 0;
}

void draw(const std::deque<Position>& snake, Position food, int score)
{
    std::cout << "\033[H\033[2J";
    std::cout << "Snake   Score: " << score << "\n";
    std::cout << '+' << std::string(board_width, '-') << "+\n";

    for (int y = 0; y < board_height; ++y)
    {
        std::cout << '|';
        for (int x = 0; x < board_width; ++x)
        {
            Position cell{x, y};
            char symbol = ' ';
            if (cell == snake.front())
                symbol = '@';
            else if (std::find(snake.begin() + 1, snake.end(), cell) != snake.end())
                symbol = 'o';
            else if (cell == food)
                symbol = '*';
            std::cout << symbol;
        }
        std::cout << "|\n";
    }
    std::cout << '+' << std::string(board_width, '-') << "+\n";
    std::cout << "Arrow keys to move, Q to quit" << std::flush;
}

Position new_food(const std::deque<Position>& snake, std::mt19937& random)
{
    std::uniform_int_distribution<int> x_distribution(0, board_width - 1);
    std::uniform_int_distribution<int> y_distribution(0, board_height - 1);
    Position food;
    do
    {
        food = {x_distribution(random), y_distribution(random)};
    } while (std::find(snake.begin(), snake.end(), food) != snake.end());
    return food;
}

bool is_opposite(Direction first, Direction second)
{
    return (first == Direction::Up && second == Direction::Down) ||
           (first == Direction::Down && second == Direction::Up) ||
           (first == Direction::Left && second == Direction::Right) ||
           (first == Direction::Right && second == Direction::Left);
}
}

int run()
{
    std::deque<Position> snake{{board_width / 2, board_height / 2},
                               {board_width / 2 - 1, board_height / 2},
                               {board_width / 2 - 2, board_height / 2}};
    Direction direction = Direction::Right;
    Position food{5, 5};
    std::mt19937 random(std::random_device{}());
    int score = 0;
    bool quit = false;
    bool game_over = false;
    TerminalMode terminal;

    while (!quit && !game_over)
    {
        if (key_available())
        {
            char key = '\0';
            const ssize_t bytes_read = read(STDIN_FILENO, &key, 1);
            if (bytes_read != 1) continue;
            Direction requested = direction;
            if (key == '\033')
            {
                char sequence[2]{};
                const ssize_t sequence_bytes = read(STDIN_FILENO, sequence, sizeof(sequence));
                if (sequence_bytes == 2 && sequence[0] == '[')
                {
                    if (sequence[1] == 'A') requested = Direction::Up;
                    if (sequence[1] == 'B') requested = Direction::Down;
                    if (sequence[1] == 'C') requested = Direction::Right;
                    if (sequence[1] == 'D') requested = Direction::Left;
                }
            }
            if (key == 'q' || key == 'Q') quit = true;
            if (!is_opposite(direction, requested)) direction = requested;
        }

        Position head = snake.front();
        if (direction == Direction::Up) --head.y;
        if (direction == Direction::Down) ++head.y;
        if (direction == Direction::Left) --head.x;
        if (direction == Direction::Right) ++head.x;

        const bool hits_wall = head.x < 0 || head.x >= board_width ||
                               head.y < 0 || head.y >= board_height;
        const bool hits_self = std::find(snake.begin(), snake.end(), head) != snake.end();
        if (hits_wall || hits_self)
        {
            game_over = true;
            break;
        }

        snake.push_front(head);
        if (head == food)
        {
            ++score;
            food = new_food(snake, random);
        }
        else
        {
            snake.pop_back();
        }

        draw(snake, food, score);
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }

    if (game_over)
        std::cout << "\nGame over! Final score: " << score << "\n";
    else if (quit)
        std::cout << "\nThanks for playing! Final score: " << score << "\n";
    return EXIT_SUCCESS;
}
}
