#include "snake_game.hpp"

#include "board.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <sys/select.h>
#include <termios.h>
#include <thread>
#include <unistd.h>

namespace snake_game
{
namespace
{
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

bool is_opposite(Direction first, Direction second)
{
    return (first == Direction::Up && second == Direction::Down) ||
           (first == Direction::Down && second == Direction::Up) ||
           (first == Direction::Left && second == Direction::Right) ||
           (first == Direction::Right && second == Direction::Left);
}

Direction read_direction(Direction current, bool& quit)
{
    char key = '\0';
    if (read(STDIN_FILENO, &key, 1) != 1) return current;
    Direction requested = current;
    if (key == '\033')
    {
        char sequence[2]{};
        if (read(STDIN_FILENO, sequence, sizeof(sequence)) == 2 && sequence[0] == '[')
        {
            if (sequence[1] == 'A') requested = Direction::Up;
            if (sequence[1] == 'B') requested = Direction::Down;
            if (sequence[1] == 'C') requested = Direction::Right;
            if (sequence[1] == 'D') requested = Direction::Left;
        }
    }
    if (key == 'q' || key == 'Q') quit = true;
    return is_opposite(current, requested) ? current : requested;
}
}

int run()
{
    Board board(board_width, board_height, {board_width / 2, board_height / 2});
    Direction direction = Direction::Right;
    int score = 0;
    bool quit = false;
    bool game_over = false;
    TerminalMode terminal;

    while (!quit && !game_over)
    {
        if (key_available()) direction = read_direction(direction, quit);
        board.player_snake().move(direction);

        if (board.collides())
        {
            game_over = true;
            break;
        }

        if (board.player_snake().head() == board.food())
        {
            board.player_snake().eat();
            ++score;
            board.place_food();
        }

        board.draw(score);
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }

    if (game_over)
        std::cout << "\nGame over! Final score: " << score << "\n";
    else if (quit)
        std::cout << "\nThanks for playing! Final score: " << score << "\n";
    return EXIT_SUCCESS;
}
}
