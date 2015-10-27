#ifndef FLAME_H
#define FLAME_H

#include "brick.h"

class Flame : public Brick
{
public:
    Flame(int, int);
    static int currentFrame;
    void accept(PaintVisitor *p){ p->visitPixmap(this); }


};

#endif // FLAME_H
