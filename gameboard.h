#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QKeyEvent>
#include <QMutableMapIterator>

#include "safe.h"
#include "floor.h"
#include "mario.h"

class Model;
class View;

class GameBoard : public QWidget
{
    Q_OBJECT

<<<<<<< HEAD
public:
    GameBoard(Model *model, QWidget *parent = 0);
=======
  public:

    GameBoard(QWidget *parent = 0);
>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
    ~GameBoard();

<<<<<<< HEAD

protected:
=======
  protected:

>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void stopGame();
    void removeDestroyed();
    void movementMario();
    void movementMap();
    bool intersect();
<<<<<<< HEAD

private:
    Model *model;
    int timerId;
    bool gameStarted;
=======


  private:

    int timerId;
>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
    int xRelatif;
    int yRelatif;
    int safeCount;
    int moveCount;
<<<<<<< HEAD
    bool moveR;
    bool moveL;
    bool isJumping;
=======
    int floorCount;

    bool gameStarted;
    bool moveR;
    bool moveL;
    bool isJumping;

    Mario *mario;
>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
};
#endif // GAMEBOARD_H
