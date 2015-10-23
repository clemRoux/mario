#ifndef PERSON_H
#define PERSON_H

#include <QPixmap>
#include <QImage>
#include <QRect>
#include <QString>
#include "paintvisitor.h"

class Person
{

  public:
    Person(int, int);
    ~Person();
    bool isDead();
    inline void setDead(bool);
    inline QRect getRect(){ return rect; }
    inline void setSrcRect(QRect srcRect){ this->srcRect = srcRect; }
    inline QRect getSrcRect(){ return srcRect; }
    inline void setRect(QRect rect){ this->rect = rect; }
    inline QRect getDieRect(){ return dieRect; }
    inline void setDieRect(QRect dieRect){ this->dieRect = dieRect; }
    inline QPixmap getMoveRSprite(){ return moveRSprite; }
    inline QPixmap getMoveLSprite(){ return moveLSprite; }
    inline QPixmap getStopSprite(){ return stopSprite; }
    inline void setMoveRSprite(QString m){ moveRSprite.load(m); }
    inline void setMoveLSprite(QString m){ moveLSprite.load(m); }
    inline void setStopSprite(QString m){ stopSprite.load(m); }
    inline bool getIsMovingR(){ return isMovingR; }
    inline bool getIsMovingL(){ return isMovingL; }
    inline bool getIsJumping(){ return isJumping; }
    inline void setIsMovingR(bool is){ this->isMovingR = is; }
    inline void setIsMovingL(bool is){ this->isMovingL = is; }
    inline void setIsJumping(bool is){ this->isJumping = is; }
    void move(int , int);
    void moveDie(int ,int );
    inline int getLife(){ return life; }
    inline void setLife(int life){ this->life = life; }
    bool intersect(QRect );
    void accept(PaintVisitor *p){ p->visitPixmap(this); }
    void setUntouchable(bool touch){ this->unTouchable = touch; }
    bool getUntouchable(){ return this->unTouchable; }

protected:
    QPixmap moveRSprite;
    QPixmap moveLSprite;
    QPixmap stopSprite;
    QPixmap jumpSprite;
    QRect rect;
    QRect dieRect;
    QRect srcRect;
    bool isMovingR;
    bool isMovingL;
    bool isJumping;
   private:
    bool dead;
    bool unTouchable = false;
    int life = 5;

};

#endif // PERSON_H
