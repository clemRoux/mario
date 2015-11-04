#include "splashscreen.h"
#include <iostream>

SplashScreen::SplashScreen(int x, int y, QString image ) : Brick(x,y, image)
{
    std::cout << ("SplashScreen created\n");
}

SplashScreen::~SplashScreen()
{
    std::cout << ("SplashScreen deleted\n");
}
