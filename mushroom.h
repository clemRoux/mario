#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "brick.h"

class Mushroom : public Brick
{
public:
    Mushroom(int, int);
    ~Mushroom();
    int getMoveCount(){ return moveCount; }
    void setmoveCount(int m){ this->moveCount = m; }

private:
    int moveCount = 40;
};

#endif // MUSHROOM_H
