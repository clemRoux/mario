#include "person.h"
#include <iostream>
#include <QDebug>
#include <QRect>

Person::Person(int x, int y)
{
    rect.translate(x, y);
    dead = false;
    isMovingR=false;
    isMovingL=false;
    isJumping=false;
}

Person::~Person()
{
    std::cout << ("Person deleted\n");
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

void Person::moveDie(int x ,int y)
{
    dieRect.moveTo(x, y);
}

bool Person::intersect(QRect r)
{
    if(r.intersects(getRect()))
       return true;
    else
        return false;
}
