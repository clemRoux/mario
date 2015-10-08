#include "background.h"
#include <iostream>


Background::Background(int x, int y ) : Brick(x,y, ":images/background.png")
{

}

Background::~Background()
{
    std::cout << ("Background deleted\n");
}
