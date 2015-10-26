#ifndef BLOOD_H
#define BLOOD_H

#include "brick.h"
class Blood : public Brick
{
public:
    Blood(int, int);
    bool getStopBlood(){ return show; }
    void setStopBlood(bool show){ this->show = show; }

    bool show = false;
};

#endif // BLOOD_H
