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

private:
    int goldNumber;

};

#endif // MARIO_H
