#include "splashscreen.h"
#include <iostream>

SplashScreen::SplashScreen(int x, int y ) : Brick(x,y, ":images/go.png")
{
    std::cout << ("SplashScreen created\n");
}

SplashScreen::~SplashScreen()
{
    std::cout << ("SplashScreen deleted\n");
}
