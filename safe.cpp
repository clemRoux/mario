#include "safe.h"
#include <iostream>

Safe::Safe(int x, int y ) : Brick(x,y, ":images/safegold.png")
{
}

Safe::~Safe()
{
    std::cout << ("Safe deleted\n");
}
