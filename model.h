#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QFile>
#include <QString>
#include <splashscreen.h>
#include "header.h"
#include "background.h"
#include "mushroom.h"
#include <QTextStream>
#include <QList>

class Safe;
class Floor;
class Mario;

//inline enum Count { MOVE, SAFE, FLOOR };
class Brick;

class Model
{
public:
    Model();
    ~Model();
    void createBrick(QList<int> , int );
    void brickOrganisation();
    QMap<int, Brick*> *getCompteur(){ return compteur; }
    inline Mario *getMario(){ return mario; }
    SplashScreen *getSplashScreen(){ return splashScreen; }
    Header *getHeader(){ return header; }
    inline QMap<int, Safe*> *getSafes(){ return safes; }
    inline QMap<int, Floor*> *getFloors(){ return floors; }
    inline QMap<int, Background*> *getBackground(){ return background; }
    inline QMap<int, Mushroom*> *getMushroom(){ return mushroom; }
    inline int getBackgroundCount(){ return backgroundCount; }
    inline void setBackgroundCount(){ this->backgroundCount++; }
    inline int getMushroomCount(){ return mushroomCount; }
    inline void setMushroomCount(){ this->mushroomCount++; }
    inline void setSafes(QMap<int,Safe*> *safes){ this->safes = safes; }
    inline void setFloors(QMap<int,Floor*> *floors){ this->floors = floors; }
    static int const brickSize = 50;
    static int const Hauteur =500;
    static int const Longueur =600;
    static int const NbrBrickVisible = 12;

private:
    QMap<int, Safe*> *safes;
    QMap<int, Mushroom*> *mushroom;
    QMap<int, Floor*> *floors;
    QMap<int, Brick*> *compteur;
    QMap<int, Background*> *background;
    QList<int> ligne1;
    QList<int> ligne2;
    QList<int> ligne3;
    QList<int> ligne4;
    QList<int> ligne5;
    Mario *mario;
    SplashScreen *splashScreen;
    Header *header;
    int floorCount;
    int safeCount;
    int backgroundCount;
    int mushroomCount;
    int mapPosition;
};

#endif // MODEL_H
