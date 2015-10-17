#include "gold.h"
#include <iostream>

Gold::Gold(int x, int y ) : Brick(x,y, ":images/gold_sprites.png")
{
    this->sprite = QPixmap(":images/gold_sprites.png");
    this->setRect(QRect(x, y, sprite.width()/3, sprite.height()));
}

Gold::~Gold()
{
     std::cout << ("Gold deleted\n");
}
