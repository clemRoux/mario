
#include "gameboard.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>

GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
{

  timerId = startTimer(10);
  gameStarted = true;
  floorCount=0;
  floors = new QMap<int,Floor *>;
  safes = new QMap<int,Safe *>;
  /*x = 0;
  gameOver = FALSE;
  gameWon = FALSE;
  paused = FALSE;
  gameStarted = FALSE;
  ball = new Ball();
  paddle = new Paddle();


  int k = 0;
  for (int i=0; i<5; i++) {
    for (int j=0; j<6; j++) {
      bricks[k] = new Brick(j*40+30, i*10+50);
      k++;
    }
  }*/
  for (int i=0; i<12; i++) {
      for (int j=0; j<2; j++) {
  Floor* k =new Floor(i*50,450-j*50);
  floors->insert(floorCount,k);
  ++floorCount;
      }
  }
}

GameBoard::~GameBoard() {

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
 /*delete ball;
 delete paddle;
 for (int i=0; i<30; i++) {
   delete bricks[i];
 }*/
}

void GameBoard::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);

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
    /*painter.drawImage(ball->getRect(),
        ball->getImage());
    painter.drawImage(paddle->getRect(),
        paddle->getImage());

    for (int i=0; i<30; i++) {
        if (!bricks[i]->isDestroyed())
          painter.drawImage(bricks[i]->getRect(),
              bricks[i]->getImage());
    }
  }*/
}

void GameBoard::timerEvent(QTimerEvent *event)
{
 /* ball->autoMove();
  checkCollision();*/
  removeDestroyed();
  repaint();
}


void GameBoard::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        {
            int x0=0;
            int y0=0;
            QMap< int,Floor *>::const_iterator i = floors->constBegin();
            while (i != floors->constEnd()) {
                if(floorCount/2>12){
                    x0=i.value()->getRect().x();
                    for (int k=1; k<=5; k++)
                    i.value()->moveRight(x0++);
                }
                ++i;
            }
            x0=0;
            QMap< int,Floor *>::const_iterator i0= floors->constBegin();
            while (i0 != floors->constEnd()) {
                if(i0.value()->getRect().x()>550){
                   if(floorCount/2>12){
                        i0.value()->setDestroyed(true);
                        x0=i0.value()->getRect().x();
                        y0=i0.value()->getRect().y();
                        Floor* k =new Floor(x0-11*50,y0);
                        floors->insert(floorCount-12,k);
                        --floorCount;
                    }
            }
            ++i0;
        }


        }
        break;
    case Qt::Key_Right:
        {
            int x0=0;
            int y0=0;
            QMap< int,Floor *>::const_iterator i = floors->constBegin();
            while (i != floors->constEnd()) {
            x0=i.value()->getRect().x();
            for (int k=1; k<=5; k++)
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
                    ++floorCount;
                }
                ++i0;
            }
        }
        break;
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
    case Qt::Key_Escape:
        {
          stopGame();
          qApp->exit();
        }
        break;
    default:
        QWidget::keyPressEvent(event);
    }
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
