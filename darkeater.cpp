#include "darkeater.h"
#include <iostream>

DarkEater::DarkEater(int x, int y) : Person(x,y)
{
    this->moveLSprite = QPixmap(":images/dark_eater.png");
    this->stopSprite = QPixmap(":images/dark_eater_die.png");
    this->rect = QRect(x, y, moveLSprite.width()/3, moveLSprite.height());
    this->isMovingL = true;
    this->dead = false;
}

DarkEater::~DarkEater(){
    std::cout << "Dark Eater deleted";
}
