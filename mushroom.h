#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "brick.h"

class Mushroom : public Brick
{
public:
    Mushroom(int, int, bool);
    ~Mushroom();
    int getMoveCount(){ return moveCount; }
    void setmoveCount(int mc){ this->moveCount = mc; }
    bool getUp(){ return up; }
    void setUp(bool upDown){ this->up = upDown; }

private:
    int moveCount = 37;
    bool up = true;

};

#endif // MUSHROOM_H
