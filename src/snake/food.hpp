namespace snake_game
{
class Food
{
public:
    Food(int board_width, int board_height, int cell_size, const std::deque<Position>& snake_positions);
    Position position() const;
    void place(const std::deque<Position>& snake_positions);
    void draw() const;
private:
    int width_;
    int height_;
    int cell_size_;
    Position position_;
    std::mt19937 random_;
    const Color food_color{251, 113, 133, 255};

}
}