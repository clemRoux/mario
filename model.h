#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QFile>
#include <QString>
#include <QList>
#include <QTextStream>
#include <QChar>

#include "splashscreen.h"
#include "header.h"
#include "background.h"
#include "mushroom.h"
#include "darkeater.h"
#include "flame.h"
#include "mystictree.h"

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
    void createBrick(QList<QChar> ,int ,int );
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
    inline QList<Flame*> *getFlame(){ return flames; }
    inline DarkEater *getDarkEater(){ return darkEater; }
    inline QList<MysticTree*> *getMysticTrees(){ return mysticTrees; }
    inline Blood *getBlood(){ return blood; }
    inline int getSpeed(){ return speed; }
    inline void setSpeed(int speed){ this->speed = speed; }
    void createMushroom(int, int);
    bool getDarkEaterBool(){ return darkEaterBool; }
    void setDarkEaterBool(bool value){ this->darkEaterBool = value; }
    static int const brickSize = 50;
    static int const Hauteur = 500;
    static int const Longueur = 1000;
    static int const NbrBrickVisible = 20;

private:
    QList<Safe*> *safes;
    QList<Mushroom*> *mushroom;
    QList<Floor*> *floors;
    QList<Brick*> *compteur;
    QList<Background*> *background;
    QList<Gold*> *golds;
    QList<Flame*> *flames;
    QList<MysticTree*> *mysticTrees;
    DarkEater *darkEater;
    Mario *mario;
    SplashScreen *splashScreen;
    Header *header;
    Blood *blood;

    QList<QChar> ligne1;
    QList<QChar> ligne2;
    QList<QChar> ligne3;
    QList<QChar> ligne4;
    QList<QChar> ligne5;
    int backgroundCount=0;
    int mapPosition = 7;
    int speed = 4;
    bool darkEaterBool;
};

#endif // MODEL_H
