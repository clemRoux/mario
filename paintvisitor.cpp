#include "paintvisitor.h"
#include "person.h"
#include "brick.h"
#include <QDebug>

PaintVisitor::PaintVisitor(QPainter *painter)
{
    this->painter = painter;
}

void PaintVisitor::visitImage(Brick *e){
    getPainter()->drawImage(e->getRect(),e->getImage());
}

void PaintVisitor::visitPixmap(Person *e){
    if(e->getIsMovingR())
        getPainter()->drawPixmap(e->getRect(), e->getMoveRSprite(), e->getSrcRect());
    else if(e->getIsMovingL())
        getPainter()->drawPixmap(e->getRect(), e->getMoveLSprite(), e->getSrcRect());
    else
        getPainter()->drawPixmap(e->getRect(), e->getStopSprite(), e->getSrcRect());
}

void PaintVisitor::visitPixmap(Brick *e){
        getPainter()->drawPixmap(e->getRect(), e->getSprite(), e->getSrcRect());
}
