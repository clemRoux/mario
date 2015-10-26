#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "brick.h"

class Background : public Brick
{
public:
    Background(int, int);
    ~Background();
    void moveBrick();


};

#endif // BACKGROUND_H
