#include "mushroom.h"
#include <QString>
#include <iostream>

Mushroom::Mushroom(int x, int y ) : Brick(x,y, ":images/champ.png")
{
    std::cout << "Mushroom created\n";
}

Mushroom::~Mushroom()
{
    std::cout << ("Mushroom deleted\n");
}



