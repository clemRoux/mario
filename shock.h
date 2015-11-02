#ifndef SHOCK_H
#define SHOCK_H

#include "brick.h"

class Shock : public Brick
{
public:
    Shock(int, int);
    void accept(PaintVisitor *p){ p->visitPixmap(this); }
    ~Shock();
    static int currentFrame;
    void setShow(bool show){ this->show = show; }
    bool getShow(){ return show; }

private:
    bool show = false;
};

#endif // SHOCK_H
