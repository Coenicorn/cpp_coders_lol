#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <inttypes.h>   
#include <math.h>

enum DIRECTIONS
{
    UP, DOWN, LEFT, RIGHT
};

class Cell
{
    public:
        Cell(int x, int y);
        int x, y;
        bool visitedPath, visitedMaze;

        // available neighbours, i.e. if down=true, there is no wall blocking the path to the down neighbour
        // only two directions are needed as with a neighbour system there will always be a cell that can have either one
        // direction in a pair of cells connected
        bool left, down;
};

class Maze
{
    public:
        Maze();
        void generate(int w, int h, int seed);
        void generatePath();
        void printMaze(std::ostream &stream);

        int width, height;
        std::vector<std::vector<Cell>> data;
    private:
        std::vector<DIRECTIONS> _getFreeNeighbours(int x, int y);
        void _generateMaze(int cX, int cY);
        bool _recurseGeneratePath(int xA, int yA, int xB, int yB);
        int _isValidPosition(int x, int y);
};

Cell::Cell(int xIn, int yIn)
{
    x = xIn;
    y = yIn;
    visitedPath = visitedMaze = false;
    left = down = false;
}

Maze::Maze(){};

void Maze::generate(int w, int h, int seed)
{
    srand(seed);

    width = w;
    height = h;

    for (int i = 0; i < width; i++)
    {
        std::vector<Cell> temp;
        for (int j = 0; j < height; j++)
        {
            Cell c(i, j);
            temp.push_back(c);
        }
        data.push_back(temp);
    }

    _generateMaze(0, 0);
}

// checks if position (x, y) is not outside of the bounds of the maze
int Maze::_isValidPosition(int x, int y)
{
    return (x < width && y < height && x >= 0 && y >= 0);
}

std::vector<DIRECTIONS> Maze::_getFreeNeighbours(int x, int y)
{
    std::vector<DIRECTIONS> validNeighbours;

    if (_isValidPosition(x-1, y) && !data[x-1][y].visitedMaze) validNeighbours.push_back(LEFT);
    if (_isValidPosition(x+1, y) && !data[x+1][y].visitedMaze) validNeighbours.push_back(RIGHT);
    if (_isValidPosition(x, y-1) && !data[x][y-1].visitedMaze) validNeighbours.push_back(UP);
    if (_isValidPosition(x, y+1) && !data[x][y+1].visitedMaze) validNeighbours.push_back(DOWN);

    return validNeighbours;
}

// generate maze starting from cell (cX, cY)
void Maze::_generateMaze(int cX, int cY)
{
    data[cX][cY].visitedMaze = true;

    std::vector<DIRECTIONS> validNeighbours = _getFreeNeighbours(cX, cY);

    while (validNeighbours.size())
    {
        int randomIndex = floor(((float)(rand()) / (float)(RAND_MAX)) * validNeighbours.size());

        switch (validNeighbours[randomIndex])
        {
            case UP:
                data[cX][cY-1].down = true;
                _generateMaze(cX, cY-1);
                break;
            case DOWN:
                data[cX][cY].down = true;
                _generateMaze(cX, cY+1);
                break;
            case RIGHT:
                data[cX+1][cY].left = true;
                _generateMaze(cX+1, cY);
                break;
            case LEFT:
                data[cX][cY].left = true;
                _generateMaze(cX-1, cY);
                break;
        }

        validNeighbours = _getFreeNeighbours(cX, cY);
    }
}

// get pseudocode'd babyyyy
void Maze::generatePath()
{
    _recurseGeneratePath(0, 0, width-1, height-1);
}

bool Maze::_recurseGeneratePath(int xA, int yA, int xB, int yB)
{
    if (data[xA][yA].visitedPath) return false;

    data[xA][yA].visitedPath = true;

    if (xA == xB && yA == yB) return true;

    // left
    if (_isValidPosition(xA-1, yA) && data[xA][yA].left && _recurseGeneratePath(xA-1, yA, xB, yB)) return true;
    // right
    if (_isValidPosition(xA+1, yA) && data[xA+1][yA].left && _recurseGeneratePath(xA+1, yA, xB, yB)) return true;
    // up
    if (_isValidPosition(xA, yA-1) && data[xA][yA-1].down && _recurseGeneratePath(xA, yA-1, xB, yB)) return true;
    // down
    if (_isValidPosition(xA, yA+1) && data[xA][yA].down && _recurseGeneratePath(xA, yA+1, xB, yB)) return true;

    data[xA][yA].visitedPath = false;

    return false;
}

void Maze::printMaze(std::ostream &stream)
{
    // top row of the maze
    stream << "+";
    for (int i = 0; i < width; i++)
        stream << "---+";
    stream << "\n";

    // go through from top to bottom, print contents for every two rows
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (!data[x][y].left)
                stream << "|";
            else 
                stream << " ";

            if (data[x][y].visitedPath)
                stream << " . ";
            else
                stream << "   ";
        }

        stream << "|\n+";

        for (int x = 0; x < width; x++)
        {
            if (!data[x][y].down)
                stream << "---+";
            else
                stream << "   +";
        }

        stream << "\n";
    }
}

int main(int argc, char **argv)
{
    Maze generatedMaze;
    
    if (argc < 3) return 1;
    if (argc == 3)
    {
        generatedMaze.generate(std::stoi(argv[2]), std::stoi(argv[1]), time(NULL));
    }
    if (argc == 4)
    {
        generatedMaze.generate(std::stoi(argv[2]), std::stoi(argv[1]), std::stoi(argv[2]));
    }
    if (argc > 4) return 1;

    generatedMaze.generatePath();

    generatedMaze.printMaze(std::cout);

    return 0;
}