#include "person.h"
#include <iostream>

Person::Person(int x, int y, QString picture)
{
  image.load(picture);
  dead = false;
  rect = image.rect();
  rect.translate(x, y);
}

Person::~Person() {

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

QImage & Person::getImage()
{
  return image;
}

bool Person::isDead()
{
  return dead;
}

void Person::setDead(bool destr)
{
  dead = destr;
}

void Person::gravity()
{
   double v_y = 4;
   double y=rect.top();
    y += v_y;
    v_y += 0.08;
    rect.moveTo(rect.left(),y);
}

void Person::moveLeft(int left ,double dir)
{
    double v_y = dir;
    double y=rect.top();
     y += v_y;
     v_y += 0.08;
    rect.moveTo(left, y);
}

void Person::moveRight(int right ,double dir)
{
    double v_y = dir;
    double y=rect.top();
     y += v_y;
     v_y += 0.08;
    rect.moveTo(right, y);
}

void Person::jump(double y)
{
    if(y<0)
    rect.moveTo(rect.left(),rect.top()-10);
}
