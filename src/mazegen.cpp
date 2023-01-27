#include <iostream>
#include <vector>

#include "mazegen.h"


//
// Header declarations
//

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
}

Maze::Maze(int w, int h)
{
    _width = w;
    _height = h;

    _generate();
}

void Maze::_generate()
{
    // fill grid with initial values
}




int main(int argc, char argv[])
{

}