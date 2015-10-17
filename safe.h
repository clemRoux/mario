#ifndef SAFE_H
#define SAFE_H

#include "brick.h"
class Safe : public Brick
{
public:

  Safe(int, int);
  ~Safe();
  int getCapacity(){ return this->capacity; }
  void setCapacity( int cap){ this->capacity = cap; }

private:
  int capacity = 0;
};

#endif // SAFE_H
