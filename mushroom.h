#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "brick.h"

class Mushroom : public Brick
{
public:
    Mushroom(int, int);
    ~Mushroom();
    int getMoveCount(){ return moveCount; }
    void setmoveCount(int mc){ this->moveCount = mc; }

private:
    int moveCount = 37;

};

#endif // MUSHROOM_H
