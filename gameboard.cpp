#include "gameboard.h"
#include <QApplication>
#include <QDebug>
#include <QRect>

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
}

int Gold::currentFrame = 0;
int Shock::currentFrame = 0;
int Flame::currentFrame = 0;
int DarkEater::currentFrame = 0;
int Brick::speed = 5;

//----------------------------------------------------------------------------------------------------------------//

GameBoard::~GameBoard()
{
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::stopGame()
{
    gameStarted = false;
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::movementMario()
{
    int y=model->getMario()->getRect().y();

    if(getIsJumping()){
        if(getIsAttacking()){
            xRelatif += 7;
        }
        else
            xRelatif+=4;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200);
        y = startJumpY-yRelatif;
        moveXMario(y);
        model->getMario()->setCurrentFrame(0);
        if(intersectTopMario()){
            xRelatif=0;
            yRelatif=0;
            startJumpY=model->getMario()->getRect().y();
            setIsJumping(false);
        }
    }

    if(intersectBottomMario()){
        xRelatif=0;
        yRelatif=0;
        startJumpY=model->getMario()->getRect().y();
        setIsJumping(false);
        moveXMario(y);

        if(getIsAttacking()){
            if(getModel()->getMario()->getIsLittle())
                getModel()->getShock()->move(model->getMario()->getRect().x() - 60, model->getMario()->getRect().y() - 25);
            else
                getModel()->getShock()->move(model->getMario()->getRect().x() - 50, model->getMario()->getRect().y());
            getModel()->getShock()->setShow(true);
            Shock::currentFrame = 0;
            setIsAttacking(false);
        }

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

    if((!intersectBottomMario() && !getIsJumping())){
        yRelatif=(-0.02*(xRelatif*xRelatif));
        xRelatif+=4;
        if(getIsAttacking()){
            xRelatif += 7;
        }
        y = startJumpY-yRelatif;
        moveXMario(y);
        model->getMario()->setCurrentFrame(0);
    }
}

void GameBoard::movementPeach()
{
    if(model->getIsPeachBool()){
        if(model->getPeach()->getIsMovingL()){

            if(peachTempo == 30){
                model->getPeach()->setCurrentFrame(model->getPeach()->getCurrentFrame() + 50);
                if (model->getPeach()->getCurrentFrame() >= 200 )
                    model->getPeach()->setCurrentFrame(0);
                peachTempo = 0;
            }
            else{
                peachTempo++;
            }
        }
    }
}

void GameBoard::movementMushroom(int i)
{
        int x=model->getMushroom()->at(i)->getRect().x();
        if(model->getMushroom()->at(i)->getMoveCount()>0){

            model->getMushroom()->at(i)->setmoveCount(model->getMushroom()->at(i)->getMoveCount() - 1);
            if(getIsMovingR() && model->getMario()->getRect().x()>=350  && !intersectRightMario()){
                if(getModel()->getMushroom()->at(i)->getUp())
                    model->getMushroom()->at(i)->move(x-Brick::speed, model->getMushroom()->at(i)->getRect().y() - 1);
                else
                    model->getMushroom()->at(i)->move(x-Brick::speed, model->getMushroom()->at(i)->getRect().y() + 1);
            }
            else {
                if(getModel()->getMushroom()->at(i)->getUp())
                    model->getMushroom()->at(i)->move(x, model->getMushroom()->at(i)->getRect().y() - 1);
                else
                    model->getMushroom()->at(i)->move(x, model->getMushroom()->at(i)->getRect().y() + 1);
            }
        }
        else
            moveBrick(x ,model->getMushroom()->at(i));
}

void GameBoard::moveBrick(int x ,Brick * b)
{
    int speed;
    if(getIsMovingR() && model->getMario()->getRect().x()>=350  && !intersectRightMario())
        speed=Brick::speed ;
    else
        speed = 0;


    if(intersectBottomBrick(b)){
        if(b->getMoveX()){
            b->move(x-speed+2, b->getRect().y());
            if(intersectRightBrick(b))
                b->setMoveX(false);
        }
        else if(!b->getMoveX()){
            b->move(x-speed-2, b->getRect().y());
            if( intersectLeftBrick(b) || b->getRect().x()<3)
                b->setMoveX(true);
        }
        b->setYR(0);
        b->setXR(0);
        b->setStartY(b->getRect().y());
    }
    else{
        b->setYR(-0.02*(b->getXR()*b->getXR()));
        b->setXR(b->getXR()+3);
        int y = b->getStartY()- b->getYR();
        if(b->getMoveX()){
            b->move(x-speed+2, y);
            if(intersectRightBrick(b))
                b->setMoveX(false);
        }
        else if(!b->getMoveX()){
            b->move(x-speed-2,y);
            if( intersectLeftBrick(b))
                b->setMoveX(true);
        }
    }
}

void GameBoard::moveXMario(int y)
{
    int x=model->getMario()->getRect().x();

    if(!intersectLeftMario() && model->getMario()->getRect().x()>=2 && getIsMovingL() ){
        x -= Brick::speed;
    }
    else if( !intersectRightMario() && model->getMario()->getRect().x()<=350  && getIsMovingR()){
         x += Brick::speed;
    }
    else if( !intersectRightMario()&& model->getMario()->getRect().x()>=350  && getIsMovingR()){
        moveMap=true;
    }
    else
        moveMap=false;
    model->getMario()->move(x,y);
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
                    model->createMushroom(model->getSafes()->at(i)->getRect().x(), model->getSafes()->at(i)->getRect().y(), true);
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
        if (model->getFloors()->at(i)->getRect().x()<=-model->brickSize || model->getFloors()->at(i)->isDestroyed())
            model->getFloors()->removeAt(i);
        if(model->getMario()->intersectBottom(model->getFloors()->at(i)->getRect()))
            return true;
    }

    for(int i = 0; i<model->getSafes()->size(); i++){
        if (model->getSafes()->at(i)->getRect().x()<=-model->brickSize || model->getSafes()->at(i)->isDestroyed()){
            qDebug()<<"delete safe";
            model->getSafes()->removeAt(i);}
        if(model->getMario()->intersectBottom(model->getSafes()->at(i)->getRect())){
            if(getIsAttacking()){
                if(model->getSafes()->at(i)->getCapacity()){
                    if(model->getSafes()->at(i)->getCapacity() == 2){
                        model->createMushroom(model->getSafes()->at(i)->getRect().x(), model->getSafes()->at(i)->getRect().y(), false);
                        model->getSafes()->at(i)->setCapacity(1);
                    }
                }else
                    model->getSafes()->at(i)->setDestroyed(true);
            }
            return true;
        }
    }
    for(int i = 0; i<model->getMysticTrees()->size(); i++){
        if(model->getMario()->intersectBottom(model->getMysticTrees()->at(i)->getRect())){
            attackMysticTree(i);
            return true;
        }
    }
    for(int i = 0; i<model->getDarkEater()->size(); i++){
        if(model->getMario()->intersectBottom(model->getDarkEater()->at(i)->getRect()) ){
            intersectYDarkEaterMario(i);
            return true;
        }
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
        if(model->getMario()->intersectLeft(model->getMysticTrees()->at(i)->getRect())){
            intersectMysticTreeMario(i);
            return true;
        }
    }

    for(int i = 0; i<model->getDarkEater()->size(); i++){
        if(model->getMario()->intersectLeft(model->getDarkEater()->at(i)->getRect()))
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
        if(model->getMario()->intersectRight(model->getMysticTrees()->at(i)->getRect())){
            intersectMysticTreeMario(i);
            return true;
        }
    }
    for(int i = 0; i<model->getDarkEater()->size(); i++){
        if(model->getMario()->intersectRight(model->getDarkEater()->at(i)->getRect()))
            return true;
    }
    return false;
}

void GameBoard::intersectGoldMario(int i)
{
    if (model->getGold()->at(i)->getRect().x()<=-model->brickSize || model->getGold()->at(i)->isDestroyed()){
        qDebug()<<"delete gold";
        model->getGold()->removeAt(i);
    }
    if(model->getMario()->intersect(model->getGold()->at(i)->getRect())){
        model->getGold()->at(i)->setDestroyed(true);
        model->getMario()->setGoldNumber(model->getMario()->getGoldNumber()+1);
    }
}

void GameBoard::intersectPeachMario()
{
    if(getModel()->getIsPeachBool()){
        if(model->getMario()->intersect(model->getPeach()->getRect())){
            getModel()->getEncart()->setShow(true);
            encartTime = 0;
            if(getModel()->getEncart()->getType() != EncartType::LOVE){
                getModel()->createEncart(getModel()->getMario()->getRect().x(), getModel()->getMario()->getRect().y() - 100, ":images/speech.png");
                getModel()->getEncart()->setType(EncartType::LOVE);
            }
        }
    }
}

void GameBoard::intersectFlameMario(int i)
{
        if(model->getMario()->intersect(model->getFlame()->at(i)->getRect()) && !model->getMario()->getUntouchable()){
            showBloodCount = 0;
            this->model->getMario()->setIsHurted(true);
        }
}

void GameBoard::intersectXDarkEaterMario(int i)
{
    if( !model->getMario()->getUntouchable()
            && !getIsAttacking()
            && !model->getDarkEater()->at(i)->isDestroyed()
            &&( model->getDarkEater()->at(i)->intersectRight(model->getMario()->getRect())||model->getDarkEater()->at(i)->intersectLeft(model->getMario()->getRect()))){

        if( !model->getMario()->getIsMovingR()&& !model->getMario()->getIsMovingL())
            model->getDarkEater()->at(i)->setMoveX(!model->getDarkEater()->at(i)->getMoveX());
        if(getModel()->getMario()->getIsMovingR() && !model->getDarkEater()->at(i)->getMoveX())
            model->getDarkEater()->at(i)->setMoveX(!model->getDarkEater()->at(i)->getMoveX());
        else if(getModel()->getMario()->getIsMovingL() && model->getDarkEater()->at(i)->getMoveX())
            model->getDarkEater()->at(i)->setMoveX(!model->getDarkEater()->at(i)->getMoveX());


        showBloodCount = 0;
        this->model->getMario()->setIsHurted(true);
    }
}

void GameBoard::intersectYDarkEaterMario(int i)
{
    if(!getModel()->getMario()->getIsMovingL()
            && !getModel()->getMario()->getIsMovingR()
            && !model->getDarkEater()->at(i)->isDestroyed()){
        getModel()->getMario()->move(getModel()->getDarkEater()->at(i)->getRect().x(), getModel()->getMario()->getRect().y());
    }
    if(!model->getDarkEater()->at(i)->isDestroyed() && getIsAttacking())
    {
        getModel()->getShock()->move(model->getDarkEater()->at(i)->getRect().x() - 50, model->getDarkEater()->at(i)->getRect().y() - 50);
        getModel()->getShock()->setShow(true);
        Shock::currentFrame = 0;
        getModel()->getDarkEater()->at(i)->setSprite(QString(":images/dark_eater_die.png"));
        model->getDarkEater()->at(i)->setDestroyed(true);
    }
}
void GameBoard::intersectMushroomMario(int i)
{
        if(model->getMario()->intersect(model->getMushroom()->at(i)->getRect())){
            model->getMushroom()->at(i)->setDestroyed(true);
            model->getMario()->setIsLittle(true);
            model->getMario()->setLife(model->getMario()->getLife() + 1);
            Brick::speed = 6;
        }
}

bool GameBoard::intersectBottomBrick(Brick * m)
{
    for(int i = 0; i<model->getFloors()->size(); i++){
        if(m->intersectBottom(model->getFloors()->at(i)->getRect()))
            return true;
    }
    for(int i = 0; i<model->getSafes()->size(); i++){
        if(m->intersectBottom(model->getSafes()->at(i)->getRect()))
            return true;
    }
    return false;
}

bool GameBoard::intersectLeftBrick(Brick * m)
{
    for(int i = 0; i<model->getFloors()->size(); i++){
        if(m->intersectLeft(model->getFloors()->at(i)->getRect()))
            return true;
    }
    for(int i = 0; i<model->getSafes()->size(); i++){
        if(m->intersectLeft(model->getSafes()->at(i)->getRect()))
            return true;
    }
    return false;
}

bool GameBoard::intersectRightBrick(Brick * m)
{
    for(int i = 0; i<model->getFloors()->size(); i++){
        if(m->intersectRight(model->getFloors()->at(i)->getRect()))
            return true;
    }

    for(int i = 0; i<model->getSafes()->size(); i++){
        if(m->intersectRight(model->getSafes()->at(i)->getRect()))
            return true;
    }
    return false;
}

void GameBoard::intersectMysticTreeMario(int i)
{
    if(!model->getMario()->getUntouchable()
        && !model->getMysticTrees()->at(i)->isDead()){
            showBloodCount = 0;
            this->model->getMario()->setIsHurted(true);
    }
}

void GameBoard::attackMysticTree(int i){
        if(!getModel()->getMysticTrees()->at(i)->isDead()
                && model->getMario()->getIsAttacking()){

            getModel()->getMysticTrees()->at(i)->setDead(true);
            model->getMysticTrees()->at(i)->setIsMovingL(false);
            getModel()->getShock()->move(model->getMysticTrees()->at(i)->getRect().x() - 50, model->getMysticTrees()->at(i)->getRect().y() - 50);
            getModel()->getShock()->setShow(true);
            Shock::currentFrame = 0;

        }
}


//-----------------------------------------------------------------------------------------------------------------------//

void GameBoard::splashScreen()
{
    if(getModel()->getSplashScreen()->getType() == SplashScreenType::GO){
        int x=model->getSplashScreen()->getRect().x();
        int y=model->getSplashScreen()->getRect().y();
        y--;
        if(model->getSplashScreen()->getRect().bottom() > 0 && model->getSplashScreen()->getIsSplashScreen())
            model->getSplashScreen()->move(x, y);
        else
            model->getSplashScreen()->setIsSplashScreen(false);
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void GameBoard::goldAnim()
{
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

void GameBoard::darkeaterAnim(int i)
{
    if(tempDarkEater == 15){
        DarkEater::currentFrame += 52;
        if (DarkEater::currentFrame >= 156)
            DarkEater::currentFrame = 1;
        tempDarkEater = 0;
    }
    else
        tempDarkEater++;
        int x=model->getDarkEater()->at(i)->getRect().x();
        if(!model->getDarkEater()->at(i)->isDestroyed()){
            moveBrick(x ,model->getDarkEater()->at(i));
            intersectXDarkEaterMario( i);
            if(model->getDarkEater()->at(i)->getMoveX())
                getModel()->getDarkEater()->at(i)->setSprite(QString(":images/dark_eater_right.png"));
            else
                getModel()->getDarkEater()->at(i)->setSprite(QString(":images/dark_eater.png"));
            model->getDarkEater()->at(i)->setSrcRect(QRect(DarkEater::currentFrame, 0, model->getDarkEater()->at(i)->getRect().width(), model->getDarkEater()->at(i)->getRect().height()));
        }
        else{
            model->getDarkEater()->at(i)->setSrcRect(QRect(0, 0, model->getDarkEater()->at(i)->getRect().width(), model->getDarkEater()->at(i)->getRect().height()));

        }
}

void GameBoard::flameAnim(int i)
{
    if(tempFlame == 10){
        Flame::currentFrame += 58;
        if (Flame::currentFrame >= 520)
            Flame::currentFrame = 3;
        tempFlame = 0;
    }
    else
        tempFlame++;
        int x=model->getFlame()->at(i)->getRect().x();
        moveBrick(x ,model->getFlame()->at(i));
        model->getFlame()->at(i)->setSrcRect(QRect(Flame::currentFrame, 0, model->getFlame()->at(i)->getRect().width(), model->getFlame()->at(i)->getRect().height()));
}

void GameBoard::BackgroundAnim(int i)
{
    if(iterBackground == 2){
        model->getBackground()->at(i)->moveBrick();
        iterBackground=0;
    }
    else{
        iterBackground++;
    }
}

void GameBoard::hurted()
{
    if(model->getMario()->getIsHurted()){
        model->getMario()->setUntouchable(true);
        if(showBloodCount >= 15){
            this->getModel()->getBlood()->setStopBlood(true);
            showBloodCount = 0;
        }
        else{
            showBloodCount++;
        }

        this->getModel()->getBlood()->move(model->getMario()->getRect().x() - 20, model->getMario()->getRect().y() - 5);

        if(getModel()->getMario()->getInvicible() == 0){
            getModel()->getEncart()->setShow(true);
            encartTime = 0;
            if(getModel()->getEncart()->getType() != EncartType::HURT){
                getModel()->createEncart(getModel()->getMario()->getRect().x(), getModel()->getMario()->getRect().y() - 100, ":images/speech_hell.png");
                getModel()->getEncart()->setType(EncartType::HURT);
            }
            model->getMario()->setLife(model->getMario()->getLife() - 1);
        }
        if(getModel()->getMario()->getInvicible() > 100){
            getModel()->getMario()->setUntouchable(false);
            getModel()->getMario()->setIsHurted(false);
            getModel()->getBlood()->setStopBlood(false);
            getModel()->getMario()->setInvicible(0);
            getModel()->getEncart()->setShow(false);
        }
        else{
            getModel()->getMario()->setInvicible(getModel()->getMario()->getInvicible() + 1);
        }
    }
}

void GameBoard::movementEncart(){
    if(getModel()->getEncart()->getShow())
        getModel()->getEncart()->move(getModel()->getMario()->getRect().x(), getModel()->getMario()->getRect().y() - 100);
}

void GameBoard::fantom()
{
    if(model->getMario()->getDieRect().bottom() > model->getMario()->getRect().top() - 200){
        int x=model->getMario()->getDieRect().x();
        int y=model->getMario()->getDieRect().y();
        model->getMario()->moveDie(x, y);
    }
    else {
        getModel()->getMario()->setUntouchable(false);
        getModel()->getMario()->setIsHurted(false);
        getModel()->getBlood()->setStopBlood(false);
    }
}

void GameBoard::movementMysticTree(int i)
{
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

bool GameBoard::GameOver(){
    if(getModel()->getMario()->getLife() < -10 || getModel()->getMario()->getRect().y() > 500){
        getModel()->getEncart()->setShow(true);
        encartTime = 0;
        if(getModel()->getSplashScreen()->getType() != SplashScreenType::GAME_OVER){
            getModel()->createGameOver(220, 100);
            getModel()->getSplashScreen()->setType(SplashScreenType::GAME_OVER);
        }
        model->getSplashScreen()->setIsSplashScreen(true);
        return true;
    }
    else
        return false;
}

bool GameBoard::Completed(){
    if(getModel()->getMario()->getGoldNumber() >= 100){
        if(getModel()->getSplashScreen()->getType() != SplashScreenType::COMPLETED){
            getModel()->createCompleted(360, 120);
            getModel()->getSplashScreen()->setType(SplashScreenType::COMPLETED);
        }
        model->getSplashScreen()->setIsSplashScreen(true);
        return true;
    }
    else
        return false;
}

void GameBoard::Peach(){
    if(getModel()->getMario()->getGoldNumber() > 2 && !getModel()->getIsPeachBool()){
        getModel()->createPeach(getModel()->getMario()->getRect().x() + 200, 340);
        getModel()->setIsPeachBool(true);
    }
}

void GameBoard::encart(){
    if(getModel()->getMario()->getGoldNumber() == 1){
        if(getModel()->getEncart()->getType() != EncartType::GOLD){
            getModel()->createEncart(getModel()->getMario()->getRect().x(), getModel()->getMario()->getRect().y() - 100, ":images/speech_gold.png");
            getModel()->getEncart()->setType(EncartType::GOLD);
        }
        encartTime = 0;
        getModel()->getEncart()->setShow(true);
    }

    if(getModel()->getEncart()->getType() == EncartType::GOLD){
        if(encartTime > 100){
            getModel()->getEncart()->setShow(false);
            getModel()->getEncart()->setType(EncartType::NONE);
        }
        else
            encartTime++;
    }
    else if(getModel()->getEncart()->getType() == EncartType::FUCK || getModel()->getEncart()->getType() == EncartType::LOVE){
        if(encartTime > 30){
            getModel()->getEncart()->setShow(false);
            getModel()->getEncart()->setType(EncartType::NONE);
        }
        else
            encartTime++;
    }
}
