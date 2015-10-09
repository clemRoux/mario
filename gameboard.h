#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QKeyEvent>
#include <QMutableMapIterator>

#include "safe.h"
#include "floor.h"
#include "mario.h"

class Model;

class GameBoard : public QWidget
{
    Q_OBJECT


public:
    GameBoard(QWidget *parent = 0);
    ~GameBoard();
    inline int getIterBackground(){ return this->iterBackground; }
    inline void setIterBackground(int iterBackground){ this->iterBackground = iterBackground; }

  protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void stopGame();
    void movementMario();
    void movementMap();
    void movementBackground();
    void splashScreen();
    void hurted();
    bool intersectBottomMario();
    bool intersectTopMario();
    bool intersectRightMario();
    bool intersectLeftMario();

private:
    Model *model;
    int timerId;
    bool gameStarted;
    int xRelatif;
    int yRelatif;
    int startJumpY;
    bool moveR;
    bool moveL;
    bool isJumping;
    bool isSplashScreen;
    int iterBackground;
    float currentFrame = 1;
    int tempMove = 0;
    qreal opacity = 1;
    bool isHurted = false;


};
#endif // GAMEBOARD_H
