#include "mario.h"
#include <iostream>

Mario::Mario(int x, int y ) : Brick(x,y, ":images/walkMario6.png")
{
}

Mario::~Mario() {

   std::cout << ("Mario deleted\n");
}

