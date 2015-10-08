#include "model.h"
#include <mario.h>
#include <safe.h>
#include <floor.h>
#include <splashscreen.h>
#include <header.h>
#include <QDebug>

Model::Model()
{
    this->floors = new QMap<int,Floor *>;
    this->safes = new QMap<int,Safe *>;
    this->mario = new Mario(100,142);
    this->splashScreen = new SplashScreen(100, 100);
    this->background = new QMap<int,Background *>;
    this->header = new Header();

    floorCount=0;

    for (int i=0; i<2; i++) {
        Background* b = new Background(i*800, 0);
        background->insert(backgroundCount, b);
        backgroundCount++;
    }

    for (int i=0; i<13; i++) {
        for (int j=0; j<2; j++) {
            Floor* k = new Floor(i*brickSize,500-brickSize-j*brickSize);
            floors->insert(floorCount,k);
            floorCount++;
        }
    }
}

Model::~Model() {
    QMap< int,Floor *>::const_iterator i = floors->constBegin();
    QMap< int,Safe *>::const_iterator e = safes->constBegin();

    while (i != floors->constEnd()) {
        delete i.value();
        ++i;
    }
    while (e != safes->constEnd()) {
        delete  e.value();
        ++e;
    }
    floors->clear();
    delete floors;
    safes->clear();
    delete safes;
    delete mario;
    delete splashScreen;
}


