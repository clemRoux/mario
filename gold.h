#ifndef GOLD_H
#define GOLD_H

#include <QPixmap>
#include <QRect>
#include <QString>

#include "brick.h"
class Gold : public Brick
{

public:
  Gold(int, int);
  inline QPixmap getSprite(){ return sprite; }
  static int currentFrame;
  ~Gold();

private:
  QPixmap sprite;
};

#endif // GOLD_H
