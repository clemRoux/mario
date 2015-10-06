#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QString>

class Safe;
class Floor;
class Mario;
//inline enum Count { MOVE, SAFE, FLOOR };

class Model
{
public:
    Model();
    ~Model();
    inline Mario *getMario(){ return mario; }
    inline QMap<int, Safe*> *getSafes(){ return safes; }
    inline QMap<int, Floor*> *getFloors(){ return floors; }
    //inline QMap<QString, int> *getCount(){ return count; }
    inline int getFloorCount(){ return floorCount; }
    inline void setFloorCount(){ this->floorCount++; }
    inline int getSafeCount(){ return safeCount; }
    inline void setSafeCount(){ this->safeCount++; }
    //inline int  getMoveCount(){ return MoveCount; }
    inline void setMario(Mario *mario){ this->mario = mario; }
    inline void setSafes(QMap<int,Safe*> *safes){ this->safes = safes; }
    inline void setFloors(QMap<int,Floor*> *floors){ this->floors = floors; }
    int const brickSize = 50;

private:
    QMap<int, Safe*> *safes;
    QMap<int, Floor*> *floors;
    //QMap<QString, int> *count;
    Mario *mario;
    int floorCount;
    int safeCount;
    //int moveCount;

    //signals:

    //public slots:
};

#endif // MODEL_H
