#include "brick.h"
#include <iostream>

Brick::Brick(int x, int y, QString picture)
{
    image.load(picture);
    destroyed = false;
    rect = image.rect();
    rect.translate(x, y);
}

Brick::~Brick()
{
    std::cout << ("Brick deleted\n");
}

QRect Brick::getRect()
{
    return rect;
}

void Brick::setRect(QRect rct)
{
    rect = rct;
}

QImage & Brick::getImage()
{
    return image;
}

bool Brick::isDestroyed()
{
    return destroyed;
}

void Brick::setDestroyed(bool destr)
{
<<<<<<< HEAD
  destroyed = destr;
}

void Brick::moveBrick(int x)
{
    rect.moveTo(x, rect.top());
}
=======
    destroyed = destr;
}

void Brick::moveBrick(int x)
{
    rect.moveTo(x, rect.top());
}

>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
