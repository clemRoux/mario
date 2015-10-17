#include "floor.h"
#include <iostream>

Floor::Floor(int x, int y ) : Brick(x,y, ":images/floor_uni.png")
{
}

Floor::~Floor()
{
    std::cout << ("Floor deleted\n");
}
