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
    inline void setSprite(QString sprite){ this->sprite.load(sprite); }
    inline QRect getSrcRect(){ return srcRect; }
    inline void setSrcRect(QRect srcRect){ this->srcRect = srcRect; }
    bool intersectBottom(QRect );
    bool intersectRight(QRect );
    bool intersectLeft(QRect );
    bool getMoveX(){return moveX;}
    void setMoveX(bool mx){this->moveX=mx;}
    void setXR(int x){this->xR=x;}
    void setYR(int y){this->yR=y;}
    void setStartY(int s){this->startY=s;}
    int getXR(){return xR;}
    int getYR(){return yR;}
    int getStartY(){return startY;}

  private:
    QImage image;
    bool destroyed;
    bool moveX=true;
    int xR=0;
    int yR=0;
    int startY;
protected:
    QRect rect;
    QPixmap sprite;
    QRect srcRect;

};

#endif // BRICK_H
