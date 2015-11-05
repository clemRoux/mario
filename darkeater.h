#ifndef DARKEATER_H
#define DARKEATER_H

#include "brick.h"

class DarkEater : public Brick
{
public:
    DarkEater(int, int);
    static int currentFrame;
    void accept(PaintVisitor *p){ p->visitPixmap(this); }
    ~DarkEater();
};

#endif // DARKEATER_H
