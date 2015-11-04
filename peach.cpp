#include "peach.h"

Peach::Peach(int x, int y) : Person(x,y)
{
    this->moveLSprite = QPixmap(":images/peach_sprite.png");
    this->rect = QRect(x, y, moveLSprite.width(), moveLSprite.height() );
}

