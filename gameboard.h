#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QKeyEvent>
#include <QMutableMapIterator>

#include "safe.h"
#include "floor.h"
#include "mario.h"
#include "gold.h"

class Model;

class GameBoard : public QWidget
{
    Q_OBJECT


public:
    GameBoard(QWidget *parent = 0);
    ~GameBoard();

  protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void stopGame();
    void movementMario();
    void moveXMario(int );
    void movementMap();
    void movementBackground();
    void movementMushroom();
    void splashScreen();
    void hurted();
    bool intersectBottomMario();
    bool intersectTopMario();
    bool intersectRightMario();
    bool intersectLeftMario();
    void intersectGoldMario();
    void intersectMushroomMario();
    void goldAnim();
    void movementDarkEater();

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
    float currentFrame =1;
    int tempMove = 0;
    qreal opacity = 1;
    bool isHurted = false;
    int currentGoldFrame = 0;
    int temp = 0;
    int currentDarkEaterFrame = 0;
    int darkEaterTempo = 0;


};
#endif // GAMEBOARD_H
