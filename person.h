#ifndef PERSON_H
#define PERSON_H

#include <QPixmap>
#include <QImage>
#include <QRect>
#include <QString>

class Person
{

  public:
    Person(int, int);
    ~Person();
    bool isDead();
    inline void setDead(bool);
    inline QRect getRect(){ return rect; }
    inline void setRect(QRect rect){ this->rect = rect; }
    inline QRect getDieRect(){ return dieRect; }
    inline void setDieRect(QRect dieRect){ this->dieRect = dieRect; }
    inline QImage & getImage(){ return image; }
    inline QPixmap getMoveRSprite(){ return moveRSprite; }
    inline QPixmap getMoveLSprite(){ return moveLSprite; }
    inline QPixmap getStopSprite(){ return stopSprite; }
    void move(int , int);
    void moveDie(int ,int );
    inline int getLife(){ return life; }
    inline void setLife(int life){ this->life = life; }

protected:
    QPixmap moveRSprite;
    QPixmap moveLSprite;
    QPixmap stopSprite;
    QPixmap jumpSprite;
    QRect rect;
    QRect dieRect;

   private:
    QImage image;
    QPixmap imageMap;
    bool dead;
    int life = 5;

};

#endif // PERSON_H
