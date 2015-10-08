#include "person.h"
#include <iostream>
#include <QDebug>
#include <QRect>

Person::Person(int x, int y, QString picture)
{
    //image.load(picture);
    dead = false;
    this->imageMap = QPixmap(picture);
    qDebug() << imageMap.size();
    rect = QRect(x, y, 39, 70);
    //rect = image.rect();
    //rect.translate(x, y);
}

Person::~Person()
{
    std::cout << ("Person deleted\n");
}

QRect Person::getRect()
{
    return rect;
}

void Person::setRect(QRect rct)
{
    rect = rct;
}

bool Person::isDead()
{
    return dead;
}

void Person::setDead(bool destr)
{
    dead = destr;
}

void Person::move(int x ,int y)
{
    rect.moveTo(x, y);
}
