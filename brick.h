#ifndef BRICK_H
#define BRICK_H

#include <QImage>
#include <QRect>
#include <QString>

class Brick
{

  public:

    Brick(int, int , QString );
    ~Brick();
    bool isDestroyed();
    void setDestroyed(bool);
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();
<<<<<<< HEAD
    void moveLeft(int );
=======
>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
    void moveBrick(int );

  private:

    QImage image;
    QRect rect;
    bool destroyed;

};

#endif // BRICK_H
