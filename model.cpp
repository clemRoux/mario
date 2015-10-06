#include "model.h"
#include <mario.h>
#include <safe.h>
#include <floor.h>

Model::Model()
{
    this->floors = new QMap<int,Floor *>;
    this->safes = new QMap<int,Safe *>;
    this->mario = new Mario(200,342);
    floorCount=0;

    for (int i=0; i<13; i++) {
        for (int j=0; j<2; j++) {
            Floor* k = new Floor(i*brickSize,450-j*brickSize);
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
}


