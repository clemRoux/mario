#include "darkeater.h"
#include <iostream>

DarkEater::DarkEater(int x, int y) : Person(x,y)
{
    this->moveLSprite = QPixmap(":images/dark_eater.png");
    this->rect = QRect(x, y, moveLSprite.width()/3, moveLSprite.height());
}

DarkEater::~DarkEater(){
    std::cout << "Dark Eater deleted";
}

