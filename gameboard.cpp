
#include "gameboard.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>

GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
{

  timerId = startTimer(15);
  gameStarted = true;
  floorCount=0;
  floors = new QMap<int,Floor *>;
  safes = new QMap<int,Safe *>;
  mario = new Mario(200,340);
  dirY=0;
  moveL=false;
  moveR=false;
  for (int i=0; i<11; i++) {
      for (int j=0; j<2; j++) {
  Floor* k =new Floor(i*50,450-j*50);
  floors->insert(floorCount,k);
  floorCount++;
      }
  }
}

GameBoard::~GameBoard() {
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
  /*if (gameOver) {
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width("Game Over");

    painter.setFont(font);
    int h = height();
    int w = width();

    painter.translate(QPoint(w/2, h/2));
    painter.drawText(-textWidth/2, 0, "Game Over");
  }
  else if(gameWon) {
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width("Victory");

    painter.setFont(font);
    int h = height();
    int w = width();

    painter.translate(QPoint(w/2, h/2));
    painter.drawText(-textWidth/2, 0, "Victory");
  }
  else {*/
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
 if(!intersect() && dirY>=0 && !moveR && !moveL)
      mario->gravity();
 else if(moveR)
     movementRight();
 else if(moveL)
     movementLeft();
 else if(dirY<0 && !moveR && !moveL){
      mario->jump(dirY);
      dirY+= 0.01;
 }
  removeDestroyed();
  repaint();
}


void GameBoard::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space && intersect())
    {
        dirY=-15;
    }
    else if(event->key() == Qt::Key_Right)
    {
        moveR=true;
    }

    else if(event->key() == Qt::Key_Left)
    {
        moveL=true;
    }


   /* case Qt::Key_P:
        {
          pauseGame();
        }
        break;
    case Qt::Key_Space:
        {
          startGame();
        }
        break;*/
    else if (event->key() == Qt::Key_Escape)
        {
          stopGame();
          qApp->exit();
        }

    else
        QWidget::keyPressEvent(event);
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
}

void GameBoard::movementLeft()
{
    if(mario->getRect().x()<250 && mario->getRect().x()>=5)
    {
        int x0=mario->getRect().x();
       if (intersect())
       {
              mario->moveLeft(x0-10, 0);
       }
       else

           mario->moveLeft(x0-10 , dirY);
    }
    moveL=false;
}

void GameBoard::movementRight()
{
    if(mario->getRect().x()<230 && mario->getRect().x()>=-2)
    {
       int x0=mario->getRect().x();
       for (int i=1; i<=10; i++)
       mario->moveRight(x0++,0);
    }
    else{
        int x0=0;
        int y0=0;
        QMap< int,Floor *>::const_iterator i = floors->constBegin();
        while (i != floors->constEnd()) {
            x0=i.value()->getRect().x();
            for (int k=1; k<=10; k++)
            i.value()->moveLeft(x0--);
            ++i;
        }
        x0=0;
        QMap< int,Floor *>::const_iterator i0= floors->constBegin();
        while (i0 != floors->constEnd()) {
            if(i0.value()->getRect().x()<-50){
                i0.value()->setDestroyed(true);
                x0=i0.value()->getRect().x();
                y0=i0.value()->getRect().y();
                Floor* k =new Floor(x0+11*50,y0);
                floors->insert(floorCount,k);
                qDebug() << "create Floor:" << floorCount ;
                floorCount++;
            }
            ++i0;
        }
    }
    moveR=false;
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
