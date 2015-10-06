#include "gameboard.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include "model.h"

GameBoard::GameBoard(Model *model, QWidget *parent)
    : model(model), QWidget(parent)
{
<<<<<<< HEAD
    this->model = model;
    timerId = startTimer(5);
    gameStarted = true;
    moveL=false;
    moveR=false;
    isJumping=false;
    xRelatif = -100;
    yRelatif = 0;
    safeCount=0;
    moveCount=0;

=======
    timerId = startTimer(10);

    gameStarted = true;
    moveL=false;
    moveR=false;
    isJumping=false;

    floors = new QMap<int,Floor *>;
    safes = new QMap<int,Safe *>;

    mario = new Mario(200,341);

    floorCount=0;
    xRelatif = -100;
    yRelatif = 0;
    safeCount=0;
    moveCount=0;

    for (int i=0; i<13; i++) {
        for (int j=0; j<2; j++) {
            Floor* k =new Floor(i*50,450-j*50);
            floors->insert(floorCount,k);
            floorCount++;
        }
    }
>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
}

GameBoard::~GameBoard()
{
    killTimer(timerId);
    delete model;

<<<<<<< HEAD
=======
    while (i != floors->constEnd()) {
        delete i.value();
         ++i;
     }
     while (e != safes->constEnd()) {
        delete  e.value();
        ++e;
     }

    floors->clear();
    delete floors;
    safes->clear();
    delete safes;
    delete mario;
>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
}

void GameBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
<<<<<<< HEAD
    painter.drawImage(model->getMario()->getRect(), model->getMario()->getImage());

    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    QMap< int,Safe *>::const_iterator e = model->getSafes()->constBegin();

    while (i != model->getFloors()->constEnd()) {
=======
    painter.drawImage(mario->getRect(),mario->getImage());

    QMap< int,Floor *>::const_iterator i = floors->constBegin();
    QMap< int,Safe *>::const_iterator e = safes->constBegin();

    while (i != floors->constEnd()) {
>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
        painter.drawImage(i.value()->getRect(),i.value()->getImage());
        ++i;
    }
    while (e != model->getSafes()->constEnd()) {
        painter.drawImage(e.value()->getRect(),e.value()->getImage());
        ++e;
    }
}

void GameBoard::timerEvent(QTimerEvent *event)
{
    movementMario();
    removeDestroyed();
    repaint();
}


void GameBoard::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right && !moveL)
    {
        moveR=true;
    }
    else if(event->key() == Qt::Key_Left && !moveR)
    {
        moveL=true;
    }
    else if(event->key() == Qt::Key_Space && intersect())
    {
        isJumping=true;
    }
    else if (event->key() == Qt::Key_Escape )
    {
        stopGame();
        qApp->exit();
    }
    else
        event->ignore();
}

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

void GameBoard::stopGame()
{
    killTimer(timerId);
    gameStarted = false;
}

void GameBoard::removeDestroyed()
{
    QMutableMapIterator<int ,Floor * > i(*model->getFloors());
    while (i.hasNext()) {
        i.next();
        if (i.value()->isDestroyed() ){
            qDebug() << "Remove Floor:" << i.key() ;
            i.remove();
        }
    }
<<<<<<< HEAD
    QMutableMapIterator<int ,Safe * > k(*model->getSafes());
=======
    QMutableMapIterator<int ,Safe * > k(*safes);
>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
    while (k.hasNext()) {
        k.next();
        if (k.value()->isDestroyed() ){
            qDebug() << "Remove Safe:" << k.key() ;
            k.remove();
        }
    }
}

<<<<<<< HEAD
void GameBoard::movementMario()
{
    int y=model->getMario()->getRect().y();
    int x=model->getMario()->getRect().x();
    //Count type=move;
    //QList<QString> valuesList = model->getCount().values();
    if(isJumping )
    {
        xRelatif+=2;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200);
        y = 334-yRelatif;
        if(moveL && model->getMario()->getRect().x()>=2){
            x-=2;
        moveCount--;        }
        else if(moveR && model->getMario()->getRect().x()<=240){
            x+=2;
            moveCount++;
        }
        else if(moveR && model->getMario()->getRect().x()>=240){
            movementMap();
            moveCount++;
        }
        model->getMario()->move(x,y);

    }

    if(intersect())
    {
        xRelatif=-100;
        yRelatif=0;
        isJumping=false;
        if(moveL && model->getMario()->getRect().x()>=2){
            x-=2;
            moveCount--;
        }
        else if(moveR && model->getMario()->getRect().x()<=240){
            x+=2;
            moveCount++;
        }
        else if(moveR && model->getMario()->getRect().x()>=240){
            movementMap();
            moveCount++;
=======
void GameBoard::movementMap()
{
    int x0=0;
    int y0=0;

    QMap< int,Floor *>::const_iterator i = floors->constBegin();
    while (i != floors->constEnd()) {
        x0=i.value()->getRect().x();
        i.value()->moveBrick(x0-2);
        ++i;
    }

    QMap< int,Safe *>::const_iterator j = safes->constBegin();
    while (j != safes->constEnd()) {
        x0=j.value()->getRect().x();
        j.value()->moveBrick(x0-2);
        ++j;
    }

    QMap< int,Floor *>::const_iterator i0= floors->constBegin();
    while (i0 != floors->constEnd()) {
        if(i0.value()->getRect().x()<-50){
            i0.value()->setDestroyed(true);
            x0=i0.value()->getRect().x();
            y0=i0.value()->getRect().y();
            Floor* k =new Floor(x0+13*50,y0);
            floors->insert(floorCount,k);
            qDebug() << "create Floor:" << floorCount ;
            floorCount++;
        }
        ++i0;
    }

    if(moveCount==200){
        x0=650;
        y0=200;
        Safe* k =new Safe(x0,y0);
        safes->insert(safeCount,k);
        qDebug() << "create Safe:" << safeCount ;
        safeCount++;
    }

    QMap< int,Safe *>::const_iterator j0= safes->constBegin();
    while (j0 != safes->constEnd()) {
        if(j0.value()->getRect().x()<-50){
            j0.value()->setDestroyed(true);
        }
        ++j0;
    }
}

void GameBoard::movementMario()
{
    int y=mario->getRect().y();
    int x=mario->getRect().x();

    if(isJumping )
    {
        xRelatif+=2;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200);
        y = 334-yRelatif;
        if(moveL && mario->getRect().x()>=2){
            x-=2;
            moveCount--;
        }
        else if(moveR && mario->getRect().x()<=240){
            x+=2;
            moveCount++;
        }
        else if(moveR && mario->getRect().x()>=240){
            movementMap();
            moveCount++;
        }
        mario->move(x,y);

    }

    if(intersect())
    {
        xRelatif=-100;
        yRelatif=0;
        isJumping=false;
        if(moveL && mario->getRect().x()>=2){
            x-=2;
            moveCount--;
        }
        else if(moveR && mario->getRect().x()<=240){
            x+=2;
            moveCount++;
        }
        else if(moveR && mario->getRect().x()>=240){
            movementMap();
            moveCount++;
        }
        mario->move(x,y);
    }
}


bool GameBoard::intersect()
{
    QMap< int,Floor *>::const_iterator i = floors->constBegin();
    while (i != floors->constEnd()) {
        if ((mario->getRect()).intersects(i.value()->getRect())){
            return true;
>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
        }
        model->getMario()->move(x,y);
    }
}

void GameBoard::movementMap()
{
    int x0=0;
    int y0=0;

    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        x0=i.value()->getRect().x();
        i.value()->moveBrick(x0-2);
        ++i;
    }

    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        x0=j.value()->getRect().x();
        j.value()->moveBrick(x0-2);
        ++j;
    }

    QMap< int,Floor *>::const_iterator i0= model->getFloors()->constBegin();
    while (i0 != model->getFloors()->constEnd()) {
        if(i0.value()->getRect().x() < -model->brickSize){
            i0.value()->setDestroyed(true);
            x0=i0.value()->getRect().x();
            y0=i0.value()->getRect().y();
            Floor* k =new Floor(x0+13*50,y0);
            model->getFloors()->insert(model->getFloorCount(),k);
            qDebug() << "create Floor:" << model->getFloorCount() ;
            model->setFloorCount();

        }
        ++i0;
    }

    if(moveCount==200){
        x0=650;
        y0=200;
        Safe* k =new Safe(x0,y0);
        model->getSafes()->insert(model->getSafeCount(), k);
        qDebug() << "create Safe:" << model->getSafeCount() ;
        model->setSafeCount();
    }

    QMap< int,Safe *>::const_iterator j0= model->getSafes()->constBegin();
    while (j0 != model->getSafes()->constEnd()) {
        if(j0.value()->getRect().x()<-50){
            j0.value()->setDestroyed(true);
        }
        ++j0;
    }
}

bool GameBoard::intersect()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    model->getFloors();
    while (i != model->getFloors()->constEnd()) {
        if ((model->getMario()->getRect()).intersects(i.value()->getRect())){
            return true;

        }
        ++i;
    }
    return false;
}
