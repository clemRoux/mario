#ifndef PERSON_H
#define PERSON_H

#include <QImage>
#include <QRect>
#include <QString>

class Person
{

  public:

    Person(int, int , QString );
    ~Person();
    bool isDead();
    inline void setDead(bool);
    QRect getRect();
    inline void setRect(QRect);
    QImage & getImage();
    void move(int , int);
    inline int getLife(){ return life; }
    inline void setLife(int life){ this->life = life; }

  private:
    QImage image;
    QRect rect;
    bool dead;
    int life = 5;

};

#endif // PERSON_H
