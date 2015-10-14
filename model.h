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
#include "darkeater.h"
#include <QTextStream>
#include <QList>

class Safe;
class Floor;
class Mario;
class Brick;
class Gold;

class Model
{
public:
    Model();
    ~Model();
    void createBrick(QList<int> , int );
    void brickOrganisation();
    inline Mario *getMario(){ return mario; }
    SplashScreen *getSplashScreen(){ return splashScreen; }
    Header *getHeader(){ return header; }
    QMap<int, Brick*> *getCompteur(){ return compteur; }
    inline QMap<int, Safe*> *getSafes(){ return safes; }
    inline QMap<int, Floor*> *getFloors(){ return floors; }
    inline QMap<int, Background*> *getBackground(){ return background; }
    inline QMap<int, Mushroom*> *getMushroom(){ return mushroom; }
    inline QMap<int, Gold*> *getGold(){ return golds; }
    inline DarkEater *getDarkEater(){ return darkEater; }
    inline int getBackgroundCount(){ return backgroundCount; }
    inline int getMushroomCount(){ return mushroomCount; }
    void createMushroom(int, int);
    static int const brickSize = 50;
    static int const Hauteur =500;
    static int const Longueur =1000;
    static int const NbrBrickVisible = 20;

private:
    QMap<int, Safe*> *safes;
    QMap<int, Mushroom*> *mushroom;
    QMap<int, Floor*> *floors;
    QMap<int, Brick*> *compteur;
    QMap<int, Background*> *background;
    QMap<int, Gold*> *golds;
    DarkEater *darkEater;
    QList<int> ligne1;
    QList<int> ligne2;
    QList<int> ligne3;
    QList<int> ligne4;
    QList<int> ligne5;
    Mario *mario;
    SplashScreen *splashScreen;
    Header *header;
    int floorCount=0;
    int safeCount=0;
    int backgroundCount=0;
    int mushroomCount=0;
    int mapPosition=0;
    int goldCount=0;
};

#endif // MODEL_H
