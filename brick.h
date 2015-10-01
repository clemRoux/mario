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

  public:
    void resetState(int,int);
    bool isDestroyed();
    void setDestroyed(bool);
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();
    void moveLeft(int );
    void moveRight(int );

  private:
    QImage image;
    QRect rect;
    int position;
    bool destroyed;

};

#endif // BRICK_H
