#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "brick.h"
class SplashScreen : public Brick
{
public:
    SplashScreen(int, int);
    ~SplashScreen();
    inline bool getIsSplashScreen(){ return isSplashScreen; }
    inline void setIsSplashScreen(bool splash){ this->isSplashScreen = splash; }


private:
    bool isSplashScreen = true;
};

#endif // SPLASHSCREEN_H
