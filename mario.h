#ifndef MARIO_H
#define MARIO_H

#include <QDebug>
#include "person.h"

class Mario : public Person
{
public:

    Mario(int, int);
    ~Mario();
    int getGoldNumber(){ return goldNumber; }
    void setGoldNumber(int goldNumber){ this->goldNumber = goldNumber; }
    bool intersectTop(QRect );
    bool intersectBottom(QRect );
    bool intersectRight(QRect );
    bool intersectLeft(QRect );
    bool getIsLittle(){ return isLittle; }
    void setIsLittle(bool little){ this->isLittle = little; }
    inline bool getIsHurted(){ return isHurted; }
    inline void setIsHurted(bool hurt){ this->isHurted = hurt; }

private:
    int goldNumber;
    bool isLittle = false;
    bool isHurted = false;
    bool hurt = false;

};

#endif // MARIO_H
