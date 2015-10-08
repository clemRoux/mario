#include "mario.h"
#include <iostream>

Mario::Mario(int x, int y ) : Person(x,y, ":images/mario_sprites.png")
{
    this->goldNumber = 0;
}

Mario::~Mario()
{
    std::cout << ("Mario deleted\n");
}



