#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QKeyEvent>
#include <QMutableMapIterator>

#include "safe.h"
#include "floor.h"
#include "mario.h"



class GameBoard : public QWidget
{
  Q_OBJECT

  public:

    GameBoard(QWidget *parent = 0);
    ~GameBoard();
    QMap<int,Safe*> *safes;
    QMap<int,Floor*> *floors;

  protected:

    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void stopGame();
    void removeDestroyed();
    void movementMario();
    void movementMap();
    bool intersect();


  private:

    int timerId;
    int xRelatif;
    int yRelatif;
    int safeCount;
    int moveCount;
    int floorCount;

    bool gameStarted;
    bool moveR;
    bool moveL;
    bool isJumping;

    Mario *mario;
};
#endif // GAMEBOARD_H
