#include "mario.h"
#include <iostream>

Mario::Mario(int x, int y ) : Person(x,y)
{
    this->moveRSprite = QPixmap(":images/mario_walk_sprites.png");
    this->moveLSprite = QPixmap(":images/mario_walk_sprites_left.png");
    this->stopSprite = QPixmap(":images/mario_stop.png");
    this->goldNumber = 0;
    this->rect = QRect(x, y, 45, moveRSprite.height() - 7);
    this->dieRect = QRect(x, y, 50, stopSprite.height()-7);

}

Mario::~Mario()
{
    std::cout << ("Mario deleted\n");
}

bool Mario::intersectTop(QRect r)
{
    if(r.intersected(getRect()).width() > 5 ){
        if(getRect().y() > r.y()){
            move(getRect().x(),r.y()+50);
            return true;
        }
    }
    else return false;
}

bool Mario::intersectBottom(QRect r)
{
    if(r.intersected(getRect()).width() > 5 ){
        if(getRect().y() < r.y()){
            move(getRect().x(),r.y() - getRect().height() + 1);
            return true;
        }
    }
    else return false;
}

bool Mario::intersectRight(QRect r)
{
    if(r.intersected(getRect()).height() > 2 ){
        if(getRect().x() < r.x())
            return true;
    }
    else return false;
}

bool Mario::intersectLeft(QRect r)
{
    if(r.intersected(getRect()).height() > 2){
        if(getRect().x() > r.x())
            return true;
    }
    else return false;
}

