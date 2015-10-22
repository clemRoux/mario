#ifndef PAINTVISITOR_H
#define PAINTVISITOR_H

#include <QPainter>
#include <QPaintDevice>
#include <QPaintEngine>

class Person;
class Brick;

class PaintVisitor
{
public:
    PaintVisitor(QPainter *painter);
    ~PaintVisitor();
    void visitImage(Brick *e);
    void visitPixmap(Brick *e);
    void visitPixmap(Person *e);
    QPainter *getPainter(){ return painter; }


private:
    QPainter *painter;
};

#endif // PAINTVISITOR_H
