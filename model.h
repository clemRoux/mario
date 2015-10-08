#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QString>
#include <splashscreen.h>
#include "header.h"
#include "background.h"


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
    SplashScreen *getSplashScreen(){ return splashScreen; }
    Header *getHeader(){ return header; }
    inline QMap<int, Safe*> *getSafes(){ return safes; }
    inline QMap<int, Floor*> *getFloors(){ return floors; }
    inline QMap<int, Background*> *getBackground(){ return background; }
    //inline QMap<QString, int> *getCount(){ return count; }
    inline int getFloorCount(){ return floorCount; }
    inline void setFloorCount(){ this->floorCount++; }
    inline int getSafeCount(){ return safeCount; }
    inline void setSafeCount(){ this->safeCount++; }
    inline int getBackgroundCount(){ return backgroundCount; }
    inline void setBackgroundCount(){ this->backgroundCount++; }
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
    SplashScreen *splashScreen;
    QMap<int, Background*> *background;
    Header *header;
    int floorCount;
    int safeCount;
    int backgroundCount;
    //int moveCount;

    //signals:

    //public slots:
};

#endif // MODEL_H
