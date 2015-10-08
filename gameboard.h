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


public:
    GameBoard(Model *model, QWidget *parent = 0);
    ~GameBoard();
    inline int getIterBackground(){ return this->iterBackground; }
    inline void setIterBackground(int iterBackground){ this->iterBackground = iterBackground; }

  protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void stopGame();
    void removeDestroyed();
    void movementMario();
    void movementMap();
    void movementBackground();
    bool intersect();
    void splashScreen();


private:
    Model *model;
    int timerId;
    bool gameStarted;

    int xRelatif;
    int yRelatif;
    int safeCount;
    int moveCount;
    int floorCount;
    bool moveR;
    bool moveL;
    bool isJumping;
    bool isSplashScreen;
    int iterBackground;
    float currentFrame = 2;
    int tempMove = 0;
};
#endif // GAMEBOARD_H
