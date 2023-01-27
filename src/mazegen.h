#include <vector>
#include <inttypes.h>

typedef uint8_t direction_t;

enum MAZE_DIRECTIONS
{
    UP, DOWN, LEFT, RIGHT
};

class Cell
{
    public:
        Cell(int x, int y);
        int x, y;
};

class Maze
{
    public:
        Maze(int w, int h);

        std::vector<direction_t> pathfind(int xA, int yA, int xB, int yB);

        int isValidPosition(int x, int y);
        Cell& getCellAt(int x, int y);

        int getWidth();
        int getHeight();

    private:
        std::vector<std::vector<int>> _data;
        int _width, _height;

        void _generate();
};