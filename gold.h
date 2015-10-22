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
  void accept(PaintVisitor *p){ p->visitPixmap(this); }
  static int currentFrame;
  ~Gold();

};

#endif // GOLD_H
