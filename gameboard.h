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
    void stopGame();
    void removeDestroyed();
    void movementRight();
    void movementLeft();
    bool intersect();
    bool moveR;
    bool moveL;
    //void movementSpace();

    /*void startGame();
    void pauseGame();
    void victory();
    void checkCollision();*/

  private:
    int timerId;
    bool gameStarted;
    int floorCount;
    Mario *mario;
    int dirY;
    /*int x;
    int timerId;
    Ball *ball;
    Paddle *paddle;
    Brick * bricks[30];
    bool gameOver;
    bool gameWon;
    bool gameStarted;
    bool paused;*/

};
#endif // GAMEBOARD_H
