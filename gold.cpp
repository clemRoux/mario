#include "gold.h"
#include <iostream>

Gold::Gold(int x, int y ) : Brick(x,y, ":images/gold_big.png")
{
}

Gold::~Gold()
{
     std::cout << ("Gold deleted\n");
}
