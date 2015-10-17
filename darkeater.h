#ifndef DARKEATER_H
#define DARKEATER_H

#include "person.h"

class DarkEater : public Person
{
public:
    DarkEater(int, int);
    ~DarkEater();
    inline int getCurrentFrame(){ return currentFrame; }
    inline void setCurrentFrame(int frame){ this->currentFrame = frame; }

private:
    int currentFrame = 0;

};

#endif // DARKEATER_H
