#include "floor.h"
#include <iostream>

Floor::Floor(int x, int y ) : Brick(x,y, ":images/Floor.png")
{
}

Floor::~Floor()
{
    std::cout << ("Floor deleted\n");
}

