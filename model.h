#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QFile>
#include <QString>
#include <QList>
#include <QTextStream>

#include "splashscreen.h"
#include "header.h"
#include "background.h"
#include "mushroom.h"
#include "darkeater.h"

class Safe;
class Floor;
class Mario;
class Brick;
class Gold;
class Blood;

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
    QList<Brick*> *getCompteur(){ return compteur; }
    inline QList<Safe*> *getSafes(){ return safes; }
    inline QList<Floor*> *getFloors(){ return floors; }
    inline QList<Background*> *getBackground(){ return background; }
    inline QList<Mushroom*> *getMushroom(){ return mushroom; }
    inline QList<Gold*> *getGold(){ return golds; }
    inline DarkEater *getDarkEater(){ return darkEater; }
    inline Blood *getBlood(){ return blood; }
    inline int getSpeed(){ return speed; }
    inline void setSpeed(int speed){ this->speed = speed; }
    void createMushroom(int, int);
    bool getDarkEaterBool(){ return darkEaterBool; }
    void setDarkEaterBool(bool value){ this->darkEaterBool = value; }
    static int const brickSize = 50;
    static int const Hauteur =500;
    static int const Longueur =1000;
    static int const NbrBrickVisible = 20;

private:
    QList<Safe*> *safes;
    QList<Mushroom*> *mushroom;
    QList<Floor*> *floors;
    QList<Brick*> *compteur;
    QList<Background*> *background;
    QList<Gold*> *golds;
    DarkEater *darkEater;
    Mario *mario;
    SplashScreen *splashScreen;
    Header *header;
    Blood *blood;

    QList<int> ligne1;
    QList<int> ligne2;
    QList<int> ligne3;
    QList<int> ligne4;
    QList<int> ligne5;
    int backgroundCount=0;
    int mapPosition=0;
    int speed = 4;
    bool darkEaterBool = false;
};

#endif // MODEL_H
