#include "gameboard.h"
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <QTimer>

#include "model.h"
#include "view.h"

GameBoard::GameBoard(Model *m, View *v) : QObject()
{
    this->model = m;
    this->view = v;
    this->view->setControl(this);
    gameStarted = true;
    xRelatif = -100;
    yRelatif = 0;
    iterBackground=0;

    timerId = startTimer(13);

    connect(this, SIGNAL(sendPaintIt()), view, SLOT(paintIt()));
}

int Gold::currentFrame = 0;
int Shock::currentFrame = 0;
int Flame::currentFrame = 0;
int Brick::speed = 5;

//----------------------------------------------------------------------------------------------------------------//

GameBoard::~GameBoard()
{
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::stopGame()
{
    killTimer(timerId);
    gameStarted = false;
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::timerEvent(QTimerEvent *event)
{
    splashScreen();
    movementMario();
    movementMushroom();
    movementDarkEater();
    movementMysticTree();
    model->brickOrganisation();
    goldAnim();
    flameAnim();
    shockAnim();
    hurted();
    emit sendPaintIt();
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::movementMario()
{
    int y=model->getMario()->getRect().y();
    if(getIsJumping() && !intersectTopMario()){
        xRelatif+=3;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200);
        y = startJumpY-yRelatif;
        moveXMario(y);
        model->getMario()->setCurrentFrame(0);
    }
    if(intersectBottomMario() || intersectTopMario()){
        xRelatif=-100;
        yRelatif=0;
        setIsJumping(false);
        moveXMario(y);
        if(getIsMovingR() && tempMove == 1){
            model->getMario()->setCurrentFrame(model->getMario()->getCurrentFrame() + 57);
            if (model->getMario()->getCurrentFrame() >= 1190 )
                model->getMario()->setCurrentFrame(0);
            tempMove = 0;
        }
        else if(getIsMovingR())
            tempMove++;
        else if(getIsMovingL() && tempMove == 1){
            model->getMario()->setCurrentFrame(model->getMario()->getCurrentFrame() - 57);
            if (model->getMario()->getCurrentFrame() <= 0 )
                model->getMario()->setCurrentFrame(1191);
            tempMove = 0;
        }
        else if(getIsMovingL())
            tempMove++;
        else
            model->getMario()->setCurrentFrame(0);
    }
    if((!intersectBottomMario() && !getIsJumping() )){
        y += 4;
        moveXMario(y);
        model->getMario()->setCurrentFrame(0);
    }
    intersectGoldMario();
    intersectMushroomMario();
    intersectDarkEaterMario();
    intersectFlameMario();
    intersectMysticTreeMario();
}

void GameBoard::movementDarkEater()
{
    if(model->getDarkEaterBool()){
        if(model->getDarkEater()->getIsMovingL()){
            model->getDarkEater()->move(model->getDarkEater()->getRect().x() - 2, model->getDarkEater()->getRect().y());
            if(darkEaterTempo == 15){
                model->getDarkEater()->setCurrentFrame(model->getDarkEater()->getCurrentFrame() + 52);
                if (model->getDarkEater()->getCurrentFrame() >= 156 )
                    model->getDarkEater()->setCurrentFrame(1);
                darkEaterTempo = 0;
            }
            else{
                darkEaterTempo++;
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------//

void GameBoard::moveXMario(int y)
{
    int x=model->getMario()->getRect().x();
    if(getIsMovingL() && model->getMario()->getRect().x()>=2 && !intersectLeftMario())
        x -= Brick::speed;
    else if(getIsMovingR() && model->getMario()->getRect().x()<=350  && !intersectRightMario())
        x += Brick::speed;
    else if(getIsMovingR() && model->getMario()->getRect().x()>=350  && !intersectRightMario())
        movementMap();
    model->getMario()->move(x,y);
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::movementMap()
{
    for(int i = 0; i<model->getFloors()->size(); i++){
        model->getFloors()->at(i)->moveBrick();
    }

    if(iterBackground == 2){
        for(int i = 0; i<model->getBackground()->size(); i++){
            model->getBackground()->at(i)->moveBrick();
        }
        iterBackground=0;
    }
    else{
        for(int i = 0; i<model->getBackground()->size(); i++){
            model->getBackground()->at(i)->move(model->getBackground()->at(i)->getRect().x(), model->getBackground()->at(i)->getRect().y());
        }
        iterBackground++;
    }

    for(int i = 0; i<model->getSafes()->size(); i++){
        model->getSafes()->at(i)->moveBrick();
    }

    for(int i = 0; i<model->getCompteur()->size(); i++){
        model->getCompteur()->at(i)->moveBrick();
    }

    for(int i = 0; i<model->getGold()->size(); i++){
        model->getGold()->at(i)->moveBrick();
    }

    for(int i = 0; i<model->getFlame()->size(); i++){
        model->getFlame()->at(i)->moveBrick();
    }

    for(int i = 0; i<model->getMysticTrees()->size(); i++){
        model->getMysticTrees()->at(i)->move(model->getMysticTrees()->at(i)->getRect().x() - Brick::speed, model->getMysticTrees()->at(i)->getRect().y());
    }

    if(model->getDarkEaterBool())
        model->getDarkEater()->move(model->getDarkEater()->getRect().x() - Brick::speed, model->getDarkEater()->getRect().y());

}

//----------------------------------------------------------------------------------------------------------------//

bool GameBoard::intersectTopMario()
{
    for(int i = 0; i<model->getFloors()->size(); i++){
        if(model->getMario()->intersectTop(model->getFloors()->at(i)->getRect()))
            return true;
    }

    for(int i = 0; i<model->getSafes()->size(); i++){
        if(model->getMario()->intersectTop(model->getSafes()->at(i)->getRect())){
            if(model->getSafes()->at(i)->getCapacity()){
                if(model->getSafes()->at(i)->getCapacity() == 2){
                    model->createMushroom(model->getSafes()->at(i)->getRect().x(), model->getSafes()->at(i)->getRect().y());
                    model->getSafes()->at(i)->setCapacity(1);
                }
            }else
                model->getSafes()->at(i)->setDestroyed(true);
            return true;
        }
    }
    return false;
}

bool GameBoard::intersectBottomMario()
{
    for(int i = 0; i<model->getFloors()->size(); i++){
        if(model->getMario()->intersectBottom(model->getFloors()->at(i)->getRect()))
            return true;
    }

    for(int i = 0; i<model->getSafes()->size(); i++){
        if(model->getMario()->intersectBottom(model->getSafes()->at(i)->getRect()))
            return true;
    }

    for(int i = 0; i<model->getMysticTrees()->size(); i++){
        if(model->getMario()->intersectBottom(model->getMysticTrees()->at(i)->getRect()))
            return true;
    }

    if(model->getDarkEaterBool()){
        if(model->getMario()->intersectBottom(model->getDarkEater()->getRect()))
            return true;
    }
    return false;
}

bool GameBoard::intersectLeftMario()
{
    for(int i = 0; i<model->getFloors()->size(); i++){
        if(model->getMario()->intersectLeft(model->getFloors()->at(i)->getRect()))
            return true;
    }
    for(int i = 0; i<model->getSafes()->size(); i++){
        if(model->getMario()->intersectLeft(model->getSafes()->at(i)->getRect()))
            return true;
    }

    for(int i = 0; i<model->getMysticTrees()->size(); i++){
        if(model->getMario()->intersectLeft(model->getMysticTrees()->at(i)->getRect()))
            return true;
    }

    if(model->getDarkEaterBool()){
        if(model->getMario()->intersectLeft(model->getDarkEater()->getRect()))
            return true;
    }
    return false;
}

bool GameBoard::intersectRightMario()
{
    for(int i = 0; i<model->getFloors()->size(); i++){
        if(model->getMario()->intersectRight(model->getFloors()->at(i)->getRect()))
            return true;
    }

    for(int i = 0; i<model->getSafes()->size(); i++){
        if(model->getMario()->intersectRight(model->getSafes()->at(i)->getRect()))
            return true;
    }

    for(int i = 0; i<model->getMysticTrees()->size(); i++){
        if(model->getMario()->intersectRight(model->getMysticTrees()->at(i)->getRect()))
            return true;
    }

    if(model->getDarkEaterBool()){
        if(model->getMario()->intersectRight(model->getDarkEater()->getRect()))
            return true;
    }

    return false;
}

void GameBoard::intersectGoldMario()
{
    for(int i = 0; i<model->getGold()->size(); i++){
        if(model->getMario()->intersect(model->getGold()->at(i)->getRect())){
            model->getGold()->at(i)->setDestroyed(true);
            model->getMario()->setGoldNumber(model->getMario()->getGoldNumber()+1);
        }
    }
}

void GameBoard::intersectFlameMario()
{
    for(int i = 0; i<model->getFlame()->size(); i++){
        if(model->getMario()->intersect(model->getFlame()->at(i)->getRect()) && !model->getMario()->getUntouchable()){
            this->model->getMario()->setIsHurted(true);
        }
    }
}

void GameBoard::intersectDarkEaterMario()
{
    if(model->getDarkEaterBool()){
        if(model->getMario()->intersectBottom(model->getDarkEater()->getRect())
                && !getModel()->getDarkEater()->isDead()
                && !model->getMario()->getUntouchable()){
            model->getDarkEater()->setIsMovingL(false);
            getModel()->getDarkEater()->setDead(true);
            getModel()->getShock()->move(model->getDarkEater()->getRect().x() - 50, model->getDarkEater()->getRect().y() - 50);
            getModel()->getShock()->setShow(true);
            Shock::currentFrame = 0;
        }
        else if((model->getMario()->intersectRight(model->getDarkEater()->getRect())
                 || model->getMario()->intersectTop(model->getDarkEater()->getRect()))
                && !model->getMario()->getUntouchable()
                && !model->getDarkEater()->isDead())
        {
            this->model->getMario()->setIsHurted(true);
        }
    }
}

void GameBoard::intersectMushroomMario()
{
    for(int i = 0; i<model->getMushroom()->size(); i++){
        if(model->getMario()->intersect(model->getMushroom()->at(i)->getRect())){
            model->getMushroom()->at(i)->setDestroyed(true);
            model->getMario()->setIsLittle(true);
            model->getMario()->setLife(model->getMario()->getLife() + 1);
            Brick::speed = 6;
        }
    }
}

void GameBoard::intersectMysticTreeMario()
{
    for(int i = 0; i<model->getMysticTrees()->size(); i++){
        if(model->getMario()->intersectBottom(model->getMysticTrees()->at(i)->getRect()) && !getModel()->getMysticTrees()->at(i)->isDead()){
            getModel()->getMysticTrees()->at(i)->setDead(true);
            model->getMysticTrees()->at(i)->setIsMovingL(false);
            getModel()->getShock()->move(model->getMysticTrees()->at(i)->getRect().x() - 50, model->getMysticTrees()->at(i)->getRect().y() - 50);
            getModel()->getShock()->setShow(true);
            Shock::currentFrame = 0;
        }
        else if((model->getMario()->intersectRight(model->getMysticTrees()->at(i)->getRect())
                 || model->getMario()->intersectLeft(model->getMysticTrees()->at(i)->getRect()))
                && !model->getMario()->getUntouchable()
                && !model->getMysticTrees()->at(i)->isDead())
        {
            this->model->getMario()->setIsHurted(true);
        }
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
    if(tempGold == 20){
        Gold::currentFrame += 40;
        if (Gold::currentFrame >= 120)
            Gold::currentFrame = 0;
        tempGold = 0;
    }
    else
        tempGold++;
}

void GameBoard::shockAnim(){
    if(tempShock == 3){
        Shock::currentFrame += 66;
        if (Shock::currentFrame >= 200){
            Shock::currentFrame = 0;
            getModel()->getShock()->setShow(false);
        }
        tempShock = 0;
    }
    else
        tempShock++;
}

void GameBoard::flameAnim(){
    if(tempFlame == 10){
        Flame::currentFrame += 58;
        if (Flame::currentFrame >= 520)
            Flame::currentFrame = 3;
        tempFlame = 0;
    }
    else
        tempFlame++;
}


void GameBoard::hurted(){
    if(model->getMario()->getIsHurted()){
        model->getMario()->setUntouchable(true);

        if(showBloodCount >= 20){
            this->getModel()->getBlood()->setStopBlood(true);
            showBloodCount = 0;
        }
        else{
            showBloodCount++;
        }

        //this->getModel()->getBlood()->move(model->getMario()->getRect().x() - 250, model->getMario()->getRect().y() - 350);
        this->getModel()->getBlood()->move(150, - 100);

        if(getModel()->getMario()->getInvicible() == 0){
            model->getMario()->setLife(model->getMario()->getLife() - 1);
        }
        if(getModel()->getMario()->getInvicible() > 100){
            getModel()->getMario()->setUntouchable(false);
            getModel()->getMario()->setIsHurted(false);
            getModel()->getBlood()->setStopBlood(false);
            getModel()->getMario()->setInvicible(0);
        }
        else{
            getModel()->getMario()->setInvicible(getModel()->getMario()->getInvicible() + 1);
        }


    }
}

void GameBoard::fantom(){
    if(model->getMario()->getDieRect().bottom() > model->getMario()->getRect().top() - 200){
        int x=model->getMario()->getDieRect().x();
        int y=model->getMario()->getDieRect().y();
        y = y - 3;
        model->getMario()->moveDie(x, y);
    }
    else {
        getModel()->getMario()->setUntouchable(false);
        getModel()->getMario()->setIsHurted(false);
        getModel()->getBlood()->setStopBlood(false);
    }
}

void GameBoard::movementMushroom(){
    for(int i = 0; i<model->getMushroom()->size(); i++){
        if(model->getMushroom()->at(i)->getMoveCount() > 0){
            model->getMushroom()->at(i)->setmoveCount(model->getMushroom()->at(i)->getMoveCount() - 1);
            if(getIsMovingR() && model->getMario()->getRect().x()>=350  && !intersectRightMario())
                model->getMushroom()->at(i)->move(model->getMushroom()->at(i)->getRect().x() - Brick::speed, model->getMushroom()->at(i)->getRect().y() - 1);
            else
                model->getMushroom()->at(i)->move(model->getMushroom()->at(i)->getRect().x(), model->getMushroom()->at(i)->getRect().y() - 1);
        }
        else if(getIsMovingR() && model->getMario()->getRect().x()>=350  && !intersectRightMario()){
            model->getMushroom()->at(i)->move(model->getMushroom()->at(i)->getRect().x() - Brick::speed, model->getMushroom()->at(i)->getRect().y());
        }
    }
}

void GameBoard::movementMysticTree(){
    for(int i = 0; i<model->getMysticTrees()->size(); i++){
        if(model->getMysticTrees()->at(i)->getIsMovingL()){
            if(model->getMysticTrees()->at(i)->getMoveCount() > 0){
                model->getMysticTrees()->at(i)->setmoveCount(model->getMysticTrees()->at(i)->getMoveCount() - 2);
                model->getMysticTrees()->at(i)->move(model->getMysticTrees()->at(i)->getRect().x(), model->getMysticTrees()->at(i)->getRect().y() - 2);
            }
            else if(model->getMysticTrees()->at(i)->getMoveCount() > - 120){
                model->getMysticTrees()->at(i)->setmoveCount(model->getMysticTrees()->at(i)->getMoveCount() - 2);
                model->getMysticTrees()->at(i)->move(model->getMysticTrees()->at(i)->getRect().x(), model->getMysticTrees()->at(i)->getRect().y() + 2);
            }
            else{
                model->getMysticTrees()->at(i)->setmoveCount(120);
            }
        }

    }
}
