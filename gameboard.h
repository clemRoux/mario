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


class GameBoard
{


public:
    GameBoard(Model *m, View *v);
    ~GameBoard();
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
    inline bool getIsMovingR(){ return isMovingR; }
    inline bool getIsMovingL(){ return isMovingL; }
    inline bool getIsJumping(){ return isJumping; }
    inline void setIsMovingR(bool is){ this->isMovingR = is; }
    inline void setIsMovingL(bool is){ this->isMovingL = is; }
    inline void setIsJumping(bool is){ this->isJumping = is; }
    inline std::tuple<> getAllObjects();
    inline Model *getModel(){ return this->model; }
    inline qreal getOpacity(){ return opacity; }
    inline void setOpacity(qreal opacity){this->opacity = opacity; }
    inline int getStartJumpY(){ return startJumpY; }
    inline void setStartJumpY(int startJumpY){this->startJumpY = startJumpY; }

private:
    Model *model;
    View *view;
    bool gameStarted;
    int xRelatif;
    int yRelatif;
    int startJumpY;
    int iterBackground;
    int tempMove = 0;
    bool isMovingR;
    bool isMovingL;
    bool isJumping;
    int marioSize;
    int darkEaterTempo = 0;
    int temp = 0;
    qreal opacity = 1;




};
#endif // GAMEBOARD_H
