#include "gameboard.h"
#include <QApplication>
#include <QDebug>
#include <QRect>
#include "model.h"
#include "view.h"
#include <tuple>

GameBoard::GameBoard(Model *m, View *v)
{
    this->model = m;
    this->view = v;
    this->view->setControl(this);
    gameStarted = true;
    isMovingR=false;
    isMovingL=false;
    isJumping=false;
    xRelatif = -100;
    yRelatif = 0;
    iterBackground=0;

}

int Gold::currentFrame = 0;


//----------------------------------------------------------------------------------------------------------------//

GameBoard::~GameBoard()
{
    delete model;
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::stopGame()
{
    view->stopTimer();
    gameStarted = false;
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::movementMario()
{
    int y=model->getMario()->getRect().y();
    if(isJumping && !intersectTopMario()){
        xRelatif+=3;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200);
        y = startJumpY-yRelatif;
        moveXMario(y);
        model->getMario()->setCurrentFrame(0);
    }
    if(intersectBottomMario() || intersectTopMario()){
        xRelatif=-100;
        yRelatif=0;
        isJumping=false;
        moveXMario(y);
        if(isMovingR && tempMove == 1){
            model->getMario()->setCurrentFrame(model->getMario()->getCurrentFrame() + 57);
            if (model->getMario()->getCurrentFrame() >= 1190 )
                model->getMario()->setCurrentFrame(0);
            tempMove = 0;
        }
        else if(isMovingR)
            tempMove++;
        else if(isMovingL && tempMove == 1){
            model->getMario()->setCurrentFrame(model->getMario()->getCurrentFrame() - 57);
            if (model->getMario()->getCurrentFrame() <= 0 )
                model->getMario()->setCurrentFrame(1191);
            tempMove = 0;
        }
        else if(isMovingL)
            tempMove++;
        else
            model->getMario()->setCurrentFrame(0);
    }
    if((!intersectBottomMario() && !isJumping )){
        y += 3;
        moveXMario(y);
        model->getMario()->setCurrentFrame(0);
    }
    intersectGoldMario();
    intersectMushroomMario();
}

void GameBoard::movementDarkEater()
{
    if(model->getDarkEater() != NULL){
        model->getDarkEater()->move(model->getDarkEater()->getRect().x() - 2, model->getDarkEater()->getRect().y());
        if(darkEaterTempo == 10){
            model->getDarkEater()->setCurrentFrame(model->getDarkEater()->getCurrentFrame() + 104);
            if (model->getDarkEater()->getCurrentFrame() >= 312 )
                model->getDarkEater()->setCurrentFrame(1);
            darkEaterTempo = 0;
        }
        else
            darkEaterTempo++;
    }
}
//----------------------------------------------------------------------------------------------------------------//

void GameBoard::moveXMario(int y)
{
    int x=model->getMario()->getRect().x();
    if(isMovingL && model->getMario()->getRect().x()>=2 && !intersectLeftMario() )
        x-=2;
    else if(isMovingR && model->getMario()->getRect().x()<=350  && !intersectRightMario())
        x+=2;
    else if(isMovingR && model->getMario()->getRect().x()>=350  && !intersectRightMario())
        movementMap();
    model->getMario()->move(x,y);
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::movementMap()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        i.value()->moveBrick();
        ++i;
    }
    QMap< int,Background *>::const_iterator k = model->getBackground()->constBegin();
    if(iterBackground== 4){
        while (k != model->getBackground()->constEnd()) {
            k.value()->moveBrick();
            ++k;
        }
        iterBackground=0;
    }
    else{
        while (k != model->getBackground()->constEnd()) {
            k.value()->move(k.value()->getRect().x(), k.value()->getRect().y());
            ++k;
        }
        iterBackground++;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        j.value()->moveBrick();
        ++j;
    }
    QMap< int,Brick *>::const_iterator s = model->getCompteur()->constBegin();
    while (s!= model->getCompteur()->constEnd()) {
        s.value()->moveBrick();
        ++s;
    }
    QMap< int,Gold *>::const_iterator g = model->getGold()->constBegin();
    while (g!= model->getGold()->constEnd()) {
        g.value()->moveBrick();
          ++g;
    }
}

//----------------------------------------------------------------------------------------------------------------//

bool GameBoard::intersectTopMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        if(model->getMario()->intersectTop(i.value()->getRect()))
            return true;
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(model->getMario()->intersectTop(j.value()->getRect())){
            if(j.value()->getCapacity()){
                if(j.value()->getCapacity() == 2){
                    model->createMushroom(j.value()->getRect().x(), j.value()->getRect().y());
                    j.value()->setCapacity(1);
                }
            }else
                j.value()->setDestroyed(true);
            return true;
        }
        ++j;
    }
    return false;
}

bool GameBoard::intersectBottomMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()){
        if(model->getMario()->intersectBottom(i.value()->getRect()))
            return true;
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(model->getMario()->intersectBottom(j.value()->getRect()))
            return true;
        ++j;
    }
    return false;
}

bool GameBoard::intersectLeftMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        if(model->getMario()->intersectLeft(i.value()->getRect()))
            return true;
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(model->getMario()->intersectLeft(j.value()->getRect()))
            return true;
        ++j;
    }
    return false;
}

bool GameBoard::intersectRightMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        if(model->getMario()->intersectRight(i.value()->getRect()))
            return true;
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(model->getMario()->intersectRight(j.value()->getRect()))
            return true;
        ++j;
    }
    return false;
}

void GameBoard::intersectGoldMario()
{
    QMap< int,Gold *>::const_iterator j = model->getGold()->constBegin();
    while (j != model->getGold()->constEnd()) {
        if(model->getMario()->intersect(j.value()->getRect())){
            j.value()->setDestroyed(true);
            model->getMario()->setGoldNumber(model->getMario()->getGoldNumber()+1);}
        ++j;
    }
}

void GameBoard::intersectMushroomMario()
{
    QMap< int,Mushroom *>::const_iterator j = model->getMushroom()->constBegin();
    while (j != model->getMushroom()->constEnd()) {
        if(model->getMario()->intersect(j.value()->getRect())){
            model->getMario()->setIsLittle(true);
            j.value()->setDestroyed(true);
        }
        ++j;
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void GameBoard::splashScreen(){
    int x=model->getSplashScreen()->getRect().x();
    int y=model->getSplashScreen()->getRect().y();
    y--;
    if(model->getSplashScreen()->getRect().bottom() > 0 && model->getSplashScreen()->getIsSplashScreen())
        model->getSplashScreen()->move(x, y);
    else
        model->getSplashScreen()->setIsSplashScreen(false);
}

//-----------------------------------------------------------------------------------------------------------------------//



void GameBoard::goldAnim(){
    if(temp == 20){
        Gold::currentFrame += 40;
        if (Gold::currentFrame >= 120)
            Gold::currentFrame = 0;
        temp = 0;
    }
    else
        temp++;
}

void GameBoard::hurted(){
    if(model->getMario()->getIsHurted()){
        if(opacity == 1)
            model->getMario()->setDieRect(QRect(model->getMario()->getRect().topLeft(), model->getMario()->getRect().bottomRight()));
        int x=model->getMario()->getDieRect().x();
        int y=model->getMario()->getDieRect().y();
        if(model->getMario()->getDieRect().bottom() > model->getMario()->getRect().top() + 20){
            y = y - 1;
            model->getMario()->moveDie(x, y);
        }
        else{
            model->getMario()->setIsHurted(false);
            model->getMario()->setLife(model->getMario()->getLife() - 1);
        }
    }
}

void GameBoard::movementMushroom(){
    QMap< int,Mushroom *>::const_iterator m = model->getMushroom()->constBegin();
    while (m != model->getMushroom()->constEnd()) {
        if(m.value()->getMoveCount()>0){
            m.value()->setmoveCount(m.value()->getMoveCount() - 1);
            if(isMovingR && model->getMario()->getRect().x()>=350  && !intersectRightMario())
                m.value()->move(m.value()->getRect().x() - 2, m.value()->getRect().y() - 1);
            else
                m.value()->move(m.value()->getRect().x(), m.value()->getRect().y() - 1);
        }
        else if(isMovingR && model->getMario()->getRect().x()>=350  && !intersectRightMario()){
            m.value()->move(m.value()->getRect().x() - 2, m.value()->getRect().y());
        }
        ++m;
    }
}
