#ifndef BRICK_H
#define BRICK_H

#include <QImage>
#include <QRect>
#include <QString>
#include "paintvisitor.h"

class Brick
{

  public:
    static int speed;
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
    void accept(PaintVisitor *p){ p->visitImage(this); }
    inline QPixmap getSprite(){ return sprite; }
    inline QRect getSrcRect(){ return srcRect; }
    inline void setSrcRect(QRect srcRect){ this->srcRect = srcRect; }

  private:
    QImage image;
    bool destroyed;
protected:
    QRect rect;
    QPixmap sprite;
    QRect srcRect;

};

#endif // BRICK_H
