#include "gameboard.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include "model.h"

GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
{
    timerId = startTimer(7);
    this->model = new Model;
    gameStarted = true;
    moveL=false;
    moveR=false;
    isJumping=false;
    xRelatif = -100;
    yRelatif = 0;
}

//-------------------------------------------------------------------------------------------------------------//

GameBoard::~GameBoard()
{
    delete model;
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(model->getMario()->getRect(), model->getMario()->getImage());

    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    QMap< int,Safe *>::const_iterator e = model->getSafes()->constBegin();

    while (i != model->getFloors()->constEnd()) {
        painter.drawImage(i.value()->getRect(),i.value()->getImage());
        ++i;
    }
    while (e != model->getSafes()->constEnd()) {
        painter.drawImage(e.value()->getRect(),e.value()->getImage());
        ++e;
    }
}

//-------------------------------------------------------------------------------------------------------------------//

void GameBoard::timerEvent(QTimerEvent *event)
{
    movementMario();
    model->brickOrganisation();
    repaint();
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right)
    {
        moveR=true;

    }
    else if(event->key() == Qt::Key_Left)
    {
        moveL=true;

    }
    else if(event->key() == Qt::Key_Space && intersectBottomMario())
    {
        isJumping=true;
        startJumpY=model->getMario()->getRect().y();
    }
    else if (event->key() == Qt::Key_Escape)
    {
        stopGame();
        qApp->exit();
    }
    else
        event->ignore();
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right )
    {
        moveR=false;

    }
    else if(event->key() == Qt::Key_Left )
    {
        moveL=false;
    }
    else
        event->ignore();
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::stopGame()
{
    killTimer(timerId);
    gameStarted = false;
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::movementMario()
{
    int y=model->getMario()->getRect().y();
    int x=model->getMario()->getRect().x();
    if(isJumping && !intersectTopMario())
    {

        xRelatif+=2;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200);
        y = startJumpY-yRelatif;

        if(moveL && model->getMario()->getRect().x()>=2 && !intersectLeftMario())
            x-=2;
        else if(moveR && model->getMario()->getRect().x()<=240 && !intersectRightMario())
            x+=2;
        else if(moveR && model->getMario()->getRect().x()>=240 && !intersectRightMario())
            movementMap();
        model->getMario()->move(x,y);
    }

    if(intersectBottomMario() || intersectTopMario())
    {
        xRelatif=-100;
        yRelatif=0;
        isJumping=false;
        if(moveL && model->getMario()->getRect().x()>=2 && !intersectLeftMario() )
            x-=2;
        else if(moveR && model->getMario()->getRect().x()<=240 && !intersectRightMario())
            x+=2;
        else if(moveR && model->getMario()->getRect().x()>=240 && !intersectRightMario() )
            movementMap();

        model->getMario()->move(x, y);
    }

    if((!intersectBottomMario() && !isJumping )){
        y+=2;
        if(moveL && model->getMario()->getRect().x()>=2 && !intersectLeftMario() )
            x-=2;
        else if(moveR && model->getMario()->getRect().x()<=240  && !intersectRightMario())
            x+=2;
        else if(moveR && model->getMario()->getRect().x()>=240  && !intersectRightMario())
            movementMap();

        model->getMario()->move(x,y);
    }
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::movementMap()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        i.value()->moveBrick();
        ++i;
    }

    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        j.value()->moveBrick();
        ++j;
    }

    QMap< int,Brick *>::const_iterator k = model->getCompteur()->constBegin();
    while (k!= model->getCompteur()->constEnd()) {
        k.value()->moveBrick();
        ++k;
    }
}

//----------------------------------------------------------------------------------------------------------------//


bool GameBoard::intersectTopMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        if(i.value()->getRect().intersected(model->getMario()->getRect()).width() > 1 ){
            if(model->getMario()->getRect().y() > i.value()->getRect().y())
                return true;
        }
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(j.value()->getRect().intersected(model->getMario()->getRect()).width() > 1 ){
            if(model->getMario()->getRect().y() > j.value()->getRect().y()){
                model->getMario()->move(model->getMario()->getRect().x(),j.value()->getRect().y()+49);
                j.value()->setDestroyed(true);
                return true;
            }

        }
        ++j;
    }
    return false;
}

bool GameBoard::intersectBottomMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        if(i.value()->getRect().intersected(model->getMario()->getRect()).width() > 1 ){
            if(model->getMario()->getRect().y() < i.value()->getRect().y()){
                model->getMario()->move(model->getMario()->getRect().x(),i.value()->getRect().y()-59);
                return true;
            }
        }
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(j.value()->getRect().intersected(model->getMario()->getRect()).width() > 1 ){
            if(model->getMario()->getRect().y() < j.value()->getRect().y()){
                model->getMario()->move(model->getMario()->getRect().x(),j.value()->getRect().y()-59);
                return true;
            }
        }
        ++j;
    }
    return false;
}

bool GameBoard::intersectLeftMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        if(i.value()->getRect().intersected(model->getMario()->getRect()).height() > 2 ){
            if(model->getMario()->getRect().x() > i.value()->getRect().x())
                return true;
        }
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(j.value()->getRect().intersected(model->getMario()->getRect()).height() > 2 ){
            if(model->getMario()->getRect().x() > j.value()->getRect().x())
                return true;
        }
        ++j;
    }
    return false;
}

bool GameBoard::intersectRightMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        if(i.value()->getRect().intersected(model->getMario()->getRect()).height() > 2 ){
            if(model->getMario()->getRect().x() < i.value()->getRect().x())
                return true;
        }
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(j.value()->getRect().intersected(model->getMario()->getRect()).height() > 2 ){
            if(model->getMario()->getRect().x() < j.value()->getRect().x())
                return true;
        }
        ++j;
    }
    return false;
}

//--------------------------------------------------------------------------------------------------------//
