#include "encart.h"
#include <QString>

Encart::Encart(int x, int y, QString image) : Brick(x, y, image)
{
    setShow(true);
}

