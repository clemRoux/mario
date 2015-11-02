#include "shock.h"

Shock::Shock(int x, int y) : Brick(x,y)
{
    this->sprite = QPixmap(":images/shock.png");
    this->setRect(QRect(x, y, sprite.width(), sprite.height() / 3));
}
