// This file is kind of unstructured in a way, as it would be way
// better to split this up into multiple files, but I don't know
// how the autograding program would respond to that so this is 
// just how it is :(

// I've noted with comments how I WOULD split up my program if 
// it were viable to do so, hope that clears things up a bit



#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <inttypes.h>   
#include <math.h>


// #################################
// Maze class declarations (maze.h)
// #################################

enum DIRECTIONS
{
    UP, DOWN, LEFT, RIGHT
};

class Cell
{
    public:
        Cell(int x, int y);
        int x, y;
        bool visited, open;
};

class Maze
{
    public:
        Maze();
        void generate(int w, int h, int seed);
        void generatePath();
        int isValidPosition(int x, int y);
        std::vector<DIRECTIONS> getNeighbourDirections(int x, int y);
        void printMaze(std::ostream &stream);

        int width, height;
        std::vector<std::vector<Cell>> data;
    private:
        void _generateMaze(int cX, int cY);
        bool _recurseGeneratePath(int xA, int yA, int xB, int yB);
};


// #################################
// Maze class definitions (maze.cpp)
// #################################

Cell::Cell(int xIn, int yIn)
{
    x = xIn;
    y = yIn;
    open = false;
    visited = false;
}

Maze::Maze(){};

void Maze::generate(int w, int h, int seed)
{
    srand(seed);

    /* magic calculation to make the input size fit the way mazes are stored

        2x2 maze:

        # # # # #
        # . . . #
        # # # . #
        # . . . #
        # # # # #

        walls are stored aswell as cells in the maze
    */
    width = w * 2 + 1;
    height = h * 2 + 1;

    // fill data array with initial closed values
    for (int i = 0; i < width; i++)
    {
        std::vector<Cell> pushData;

        for (int j = 0; j < height; j++)
        {
            Cell c(i, j);
            pushData.push_back(c);
        }

        data.push_back(pushData);
    }

    _generateMaze(1, 1);
}

// checks if position (x, y) is not outside of the bounds of the maze
int Maze::isValidPosition(int x, int y)
{
    return (x < width && y < height && x >= 0 && y >= 0);
}

// gets the neighbours of cell (x, y) in the maze
std::vector<DIRECTIONS> Maze::getNeighbourDirections(int x, int y)
{
    std::vector<DIRECTIONS> out;

    if (isValidPosition(x+2, y) && !data[x+2][y].open) out.push_back(RIGHT);
    if (isValidPosition(x-2, y) && !data[x-2][y].open) out.push_back(LEFT);
    if (isValidPosition(x, y+2) && !data[x][y+2].open) out.push_back(DOWN);
    if (isValidPosition(x, y-2) && !data[x][y-2].open) out.push_back(UP);

    return out;
}

// generate maze starting from cell (cX, cY)
void Maze::_generateMaze(int cX, int cY)
{
    data[cX][cY].open = true;

    std::vector<DIRECTIONS> validNeighbours = getNeighbourDirections(cX, cY);

    while(validNeighbours.size())
    {

        int randomIndex = floor(((float)(rand()) / (float)(RAND_MAX)) * validNeighbours.size());

        DIRECTIONS direction = validNeighbours[randomIndex];

        switch (direction)
        {
            case UP:
                data[cX][cY-1].open = true;
                _generateMaze(cX, cY-2);
                break;
            case DOWN:
                data[cX][cY+1].open = true;
                _generateMaze(cX, cY+2);
                break;
            case LEFT:
                data[cX-1][cY].open = true;
                _generateMaze(cX-2, cY);
                break;
            case RIGHT:
                data[cX+1][cY].open = true;
                _generateMaze(cX+2, cY);
                break;
        }

        validNeighbours = getNeighbourDirections(cX, cY);
    }
}

// get pseudocode'd babyyyy
void Maze::generatePath()
{
    _recurseGeneratePath(1, 1, width-2, height-2);
}

bool Maze::_recurseGeneratePath(int xA, int yA, int xB, int yB)
{
    data[xA][yA].visited = true;

    if (xA == xB && yA == yB) return true;

    if (isValidPosition(xA+1, yA) && (!data[xA+1][yA].visited && data[xA+1][yA].open && _recurseGeneratePath(xA+1, yA, xB, yB))) return true;
    if (isValidPosition(xA-1, yA) && (!data[xA-1][yA].visited && data[xA-1][yA].open && _recurseGeneratePath(xA-1, yA, xB, yB))) return true;
    if (isValidPosition(xA, yA+1) && (!data[xA][yA+1].visited && data[xA][yA+1].open && _recurseGeneratePath(xA, yA+1, xB, yB))) return true;
    if (isValidPosition(xA, yA-1) && (!data[xA][yA-1].visited && data[xA][yA-1].open && _recurseGeneratePath(xA, yA-1, xB, yB))) return true;

    data[xA][yA].visited = false;

    return false;
}

void Maze::printMaze(std::ostream &stream)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            if (y % 2 == 0)
            {
                if (x % 2 == 0)
                    stream << "+";
                else
                {
                    if (data[x][y].open)
                        stream << "   ";
                    else
                        stream << "---";
                }
            }
            else
            {
                if (x % 2 == 0)
                {
                    if (data[x][y].open) 
                        stream << " ";
                    else
                        stream << "|";
                }
                else
                {
                    if (data[x][y].visited)
                        stream << " . ";
                    else if (data[x][y].open)
                        stream << "   ";
                }
            }

        }
        stream << "\n";
    }
}


// #################################
// Main program entrypoint (main.c)
// #################################

int main(int argc, char **argv)
{
    Maze generatedMaze;

    if (argc < 3) return 1;
    if (argc == 3)
    {
        generatedMaze.generate(std::stoi(argv[1]), std::stoi(argv[2]), time(NULL));
    }
    if (argc == 4)
    {
        generatedMaze.generate(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[2]));
    }
    if (argc > 4) return 1;

    generatedMaze.generatePath();

    generatedMaze.printMaze(std::cout);

    return 0;
} // 250 lines babyyyyyyyyyyyyyyyyyyyyyyyyy leggooooo my code is shiiiiiiiiiiiiiiiiiiiiiiiiiiiii-