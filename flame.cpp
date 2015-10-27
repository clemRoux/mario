#include "flame.h"

Flame::Flame(int x, int y) : Brick(x,y)
{
    this->setSprite(QString(":images/fire.png"));
    this->rect = QRect(x, y - 10, getSprite().width()/9, getSprite().height());
}

