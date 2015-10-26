#include "background.h"
#include <iostream>


Background::Background(int x, int y ) : Brick(x,y, ":images/background.png")
{

}

Background::~Background()
{
    std::cout << ("Background deleted\n");
}

void Background::moveBrick()
{
    rect.moveTo(rect.left() - Brick::speed/2, rect.top());
}
