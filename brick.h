#ifndef BRICK_H
#define BRICK_H

#include <QImage>
#include <QRect>
#include <QString>

class Brick
{

  public:

    Brick(int ,int );
    Brick(int, int , QString );
    ~Brick();
    bool isDestroyed();
    void setDestroyed(bool);
    QRect getRect();
    void setRect(QRect);
    QImage & getImage();
    void setImage(QString i){ image.load(i); }
    void move(int ,int );
    void moveBrick();

  private:

    QImage image;
    QRect rect;
    bool destroyed;

};

#endif // BRICK_H
