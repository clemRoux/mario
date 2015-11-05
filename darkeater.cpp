#include "darkeater.h"
#include <iostream>

DarkEater::DarkEater(int x, int y) : Brick(x,y)
{
    this->setSprite(QString(":images/dark_eater.png"));
    this->rect = QRect(x, y+5, getSprite().width()/3, getSprite().height());
}

DarkEater::~DarkEater(){
    std::cout << "Dark Eater deleted";
}
