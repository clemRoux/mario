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
    void setDead(bool);
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();
    void move(int , int );

  private:

    QImage image;
    QRect rect;
    bool dead;

};

#endif // PERSON_H
