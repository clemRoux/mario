#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QList>

class Safe;
class Floor;
class Mario;
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
    inline QMap<int, Safe*> *getSafes(){ return safes; }
    inline QMap<int, Floor*> *getFloors(){ return floors; }
    inline void setMario(Mario *mario){ this->mario = mario; }
    inline void setSafes(QMap<int,Safe*> *safes){ this->safes = safes; }
    inline void setFloors(QMap<int,Floor*> *floors){ this->floors = floors; }
    static int const brickSize = 50;
    static int const Hauteur =500;
    static int const Longueur =600;
    static int const NbrBrickVisible = 12;

private:
    QMap<int, Safe*> *safes;
    QMap<int, Floor*> *floors;
    QMap<int, Brick*> *compteur;
    QList<int> ligne1;
    QList<int> ligne2;
    QList<int> ligne3;
    QList<int> ligne4;
    QList<int> ligne5;
    Mario *mario;
    int floorCount;
    int safeCount;
    int mapPosition;
};

#endif // MODEL_H
