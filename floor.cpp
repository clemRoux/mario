#include "floor.h"
#include <iostream>

Floor::Floor(int x, int y , QString picture) : Brick(x,y, picture)
{
}

Floor::~Floor()
{
    std::cout << ("Floor deleted\n");
}
