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
<<<<<<< HEAD
    void move(int , int);
=======
    void move(int , int );
>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c

  private:

    QImage image;
    QRect rect;
    bool dead;

};

#endif // PERSON_H
