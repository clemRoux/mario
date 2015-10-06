#include "gameboard.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>

GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
{
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
}

GameBoard::~GameBoard()
{
    killTimer(timerId);
    QMap< int,Floor *>::const_iterator i = floors->constBegin();
    QMap< int,Safe *>::const_iterator e = safes->constBegin();

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
}

void GameBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(mario->getRect(),mario->getImage());

    QMap< int,Floor *>::const_iterator i = floors->constBegin();
    QMap< int,Safe *>::const_iterator e = safes->constBegin();

    while (i != floors->constEnd()) {
        painter.drawImage(i.value()->getRect(),i.value()->getImage());
        ++i;
    }
    while (e != safes->constEnd()) {
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
    QMutableMapIterator<int ,Floor * > i(*floors);
    while (i.hasNext()) {
        i.next();
        if (i.value()->isDestroyed() ){
            qDebug() << "Remove Floor:" << i.key() ;
            i.remove();
        }
    }
    QMutableMapIterator<int ,Safe * > k(*safes);
    while (k.hasNext()) {
        k.next();
        if (k.value()->isDestroyed() ){
            qDebug() << "Remove Safe:" << k.key() ;
            k.remove();
        }
    }
}

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
        }
        ++i;
    }
    return false;
}

/*void GameBoard::movementSpace()
{
    int y=0;
    int ymax = mario->getRect().y()-200;
    isJumping=true;
    while(mario->getRect().y()>ymax){
        y = mario->getRect().y()-1;
        mario->moveUp(y);
    }
    isJumping=false;
}*/

/*void GameBoard::startGame()
{
  if (!gameStarted) {
    ball->resetState();
    paddle->resetState();

    for (int i=0; i<30; i++) {
      bricks[i]->setDestroyed(FALSE);
    }
    gameOver = FALSE;
    gameWon = FALSE;
    gameStarted = TRUE;
    timerId = startTimer(10);
  }
}

void GameBoard::pauseGame()
{
  if (paused) {
    timerId = startTimer(10);
    paused = FALSE;
  } else {
    paused = TRUE;
    killTimer(timerId);
   }
}



void GameBoard::victory()
{
  killTimer(timerId);
  gameWon = TRUE;
  gameStarted = FALSE;
}

void GameBoard::checkCollision()
{

  if (ball->getRect().bottom() > 400)
    stopGame();

  for (int i=0, j=0; i<30; i++) {
    if (bricks[i]->isDestroyed()) {
      j++;
    }
    if (j==30)
      victory();
  }

  if ((ball->getRect()).intersects(paddle->getRect())) {

    int paddleLPos = paddle->getRect().left();
    int ballLPos = ball->getRect().left();

    int first = paddleLPos + 8;
    int second = paddleLPos + 16;
    int third = paddleLPos + 24;
    int fourth = paddleLPos + 32;

    if (ballLPos < first) {
      ball->setXDir(-1);
      ball->setYDir(-1);
    }

    if (ballLPos >= first && ballLPos < second) {
      ball->setXDir(-1);
      ball->setYDir(-1*ball->getYDir());
    }

    if (ballLPos >= second && ballLPos < third) {
       ball->setXDir(0);
       ball->setYDir(-1);
    }

    if (ballLPos >= third && ballLPos < fourth) {
       ball->setXDir(1);
       ball->setYDir(-1*ball->getYDir());
    }

    if (ballLPos > fourth) {
      ball->setXDir(1);
      ball->setYDir(-1);
    }
  }


  for (int i=0; i<30; i++) {
    if ((ball->getRect()).intersects(bricks[i]->getRect())) {

      int ballLeft = ball->getRect().left();
      int ballHeight = ball->getRect().height();
      int ballWidth = ball->getRect().width();
      int ballTop = ball->getRect().top();

      QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
      QPoint pointLeft(ballLeft - 1, ballTop);
      QPoint pointTop(ballLeft, ballTop -1);
      QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

      if (!bricks[i]->isDestroyed()) {
        if(bricks[i]->getRect().contains(pointRight)) {
           ball->setXDir(-1);
        }

        else if(bricks[i]->getRect().contains(pointLeft)) {
           ball->setXDir(1);
        }

        if(bricks[i]->getRect().contains(pointTop)) {
           ball->setYDir(1);
        }

        else if(bricks[i]->getRect().contains(pointBottom)) {
           ball->setYDir(-1);
        }

        bricks[i]->setDestroyed(TRUE);
      }
    }
  }
}*/
