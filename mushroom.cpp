#include "mushroom.h"
#include <QString>
#include <iostream>

Mushroom::Mushroom(int x, int y , bool up) : Brick(x,y, ":images/champ.png")
{
    std::cout << "Mushroom created\n";
    this->up = up;
}

Mushroom::~Mushroom()
{
    std::cout << ("Mushroom deleted\n");
}



