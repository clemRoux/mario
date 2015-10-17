#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QKeyEvent>
#include <QMutableMapIterator>
#include "safe.h"
#include "floor.h"
#include "mario.h"
#include "gold.h"
#include "view.h"
#include "gameboard.h"
#include "darkeater.h"
#include "mushroom.h"

class GameBoard;

class View : public QWidget
{
    //Q_OBJECT

public:
    View(QWidget *parent = 0);
    void setControl(GameBoard *control){ this->control = control; }
    void stopTimer();

private:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    int timerId;
    GameBoard *control;
    int marioSize;

};

#endif // VIEW_H
