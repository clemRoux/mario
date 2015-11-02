#ifndef MYSTICTREE_H
#define MYSTICTREE_H

#include "person.h"

class MysticTree : public Person
{
public:
    MysticTree(int, int);
    ~MysticTree();
    int getMoveCount(){ return moveCount; }
    void setmoveCount(int m){ this->moveCount = m; }

private:
    int moveCount = 50;
};

#endif // MYSTICTREE_H
