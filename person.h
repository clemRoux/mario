#ifndef PERSON_H
#define PERSON_H

#include <QPixmap>
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
    inline QImage & getImage(){ return image; }
    inline QPixmap getImageMap(){ return imageMap; }
    void move(int , int);
    inline int getLife(){ return life; }
    inline void setLife(int life){ this->life = life; }
    inline int getXImageMap(){ return xImageMap; }
    inline void setXImageMap(int xImageMap){ this->xImageMap = xImageMap; }
  private:
    QImage image;
    QPixmap imageMap;
    QRect rect;
    bool dead;
    int life = 5;
    int xImageMap = 0;

};

#endif // PERSON_H
