#include "person.h"
#include <iostream>
#include <QDebug>
#include <QRect>

Person::Person(int x, int y)
{
    dead = false;
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
