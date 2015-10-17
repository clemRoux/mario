#include "view.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <tuple>
#include "model.h"

View::View(QWidget *parent): QWidget(parent)

{
    timerId = startTimer(10);

}

void View::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QMap< int,Safe *>::const_iterator e = control->getModel()->getSafes()->constBegin() ;
    QMap< int,Background *>::const_iterator b = control->getModel()->getBackground()->constBegin() ;
    QMap< int,Floor *>::const_iterator i = control->getModel()->getFloors()->constBegin();
    QMap< int,Gold *>::const_iterator g = control->getModel()->getGold()->constBegin();
    QMap< int,Mushroom *>::const_iterator m = control->getModel()->getMushroom()->constBegin() ;

    while (b != control->getModel()->getBackground()->constEnd()) {
        painter.drawImage(b.value()->getRect(),b.value()->getImage());
        ++b;
    }
    while (i != control->getModel()->getFloors()->constEnd()) {
        painter.drawImage(i.value()->getRect(),i.value()->getImage());
        ++i;
    }
    while (e != control->getModel()->getSafes()->constEnd()) {
        if(e.value()->getCapacity()==1)
            e.value()->setImage(":images/floor_uni.png");
        painter.drawImage(e.value()->getRect(),e.value()->getImage());
        ++e;
    }
    while (m != control->getModel()->getMushroom()->constEnd()) {
        painter.drawImage(m.value()->getRect(),m.value()->getImage());
        ++m;
    }
    while (g != control->getModel()->getGold()->constEnd()) {
        QRect srcRect = QRect(Gold::currentFrame, 0, g.value()->getRect().width(), g.value()->getRect().height());
        painter.drawPixmap(g.value()->getRect(), g.value()->getSprite(), srcRect);
        ++g;
    }
    if(control->getModel()->getDarkEater() != NULL){
        QRect srcRect = QRect(control->getModel()->getDarkEater()->getCurrentFrame(), 0, control->getModel()->getDarkEater()->getRect().width(), control->getModel()->getDarkEater()->getRect().height());
        painter.drawPixmap(control->getModel()->getDarkEater()->getRect(), control->getModel()->getDarkEater()->getMoveLSprite(), srcRect);
    }
    QRect sourceRect;
    if(control->getModel()->getMario()->getIsLittle()){
        control->getModel()->getMario()->setRect(QRect(control->getModel()->getMario()->getRect().x(), control->getModel()->getMario()->getRect().y(), 25, control->getModel()->getMario()->getMoveRSprite().height() - 30));
        sourceRect = QRect(control->getModel()->getMario()->getCurrentFrame()+6, 0, control->getModel()->getMario()->getRect().width()+20, control->getModel()->getMario()->getRect().height()+30);
    }
    else{
        control->getModel()->getMario()->setRect(QRect(control->getModel()->getMario()->getRect().x(), control->getModel()->getMario()->getRect().y(), 45, control->getModel()->getMario()->getMoveRSprite().height() - 7));
        sourceRect = QRect(control->getModel()->getMario()->getCurrentFrame()+6, 1, control->getModel()->getMario()->getRect().width(), control->getModel()->getMario()->getRect().height());
    }

    if(control->getIsMovingR()){
        painter.drawPixmap(control->getModel()->getMario()->getRect(), control->getModel()->getMario()->getMoveRSprite(), sourceRect);
    }
    else if(control->getIsMovingL()){
        painter.drawPixmap(control->getModel()->getMario()->getRect(), control->getModel()->getMario()->getMoveLSprite(), sourceRect);
    }
    else
        painter.drawPixmap(control->getModel()->getMario()->getRect() ,control->getModel()->getMario()->getStopSprite(), sourceRect);

    painter.drawImage(control->getModel()->getHeader()->getRect().width() - 100, control->getModel()->getHeader()->getRect().height() / 8, control->getModel()->getHeader()->getGold());
    painter.setFont(QFont("Tahoma", 12, -1, false));
    QString goldText = "x" + QString::number(control->getModel()->getMario()->getGoldNumber());
    painter.drawText(control->getModel()->getHeader()->getGoldPosition(), goldText);

    for(int i = 0 ; i < control->getModel()->getMario()->getLife() ; i++)
        painter.drawImage(control->getModel()->getHeader()->getHeart().size().height() * i, 0, control->getModel()->getHeader()->getHeart());

    if(control->getModel()->getSplashScreen()->getIsSplashScreen()){
        control->setOpacity(control->getOpacity() - 0.005);
        painter.setOpacity(control->getOpacity());
        painter.drawImage(control->getModel()->getSplashScreen()->getRect(), control->getModel()->getSplashScreen()->getImage());
    }
    else{
        control->setOpacity(1);
        painter.setOpacity(control->getOpacity());
    }
    if(control->getModel()->getMario()->getIsHurted()){
        control->setOpacity(control->getOpacity() - 0.01);
        painter.setOpacity(control->getOpacity());
        qDebug() << "HURT!!";
        painter.drawPixmap(control->getModel()->getMario()->getDieRect(), control->getModel()->getMario()->getStopSprite(), QRect(0, 1, 57, 68));
    }
}

//-------------------------------------------------------------------------------------------------------------------//

void View::timerEvent(QTimerEvent *event)
{
    control->splashScreen();
    control->movementMario();
    control->movementMushroom();
    control->movementDarkEater();
    control->hurted();
    control->getModel()->brickOrganisation();
    control->goldAnim();
    repaint();
}

//----------------------------------------------------------------------------------------------------------------//

void View::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right)
        control->setIsMovingR(true);
    else if(event->key() == Qt::Key_Left)
        control->setIsMovingL(true);
    else if(event->key() == Qt::Key_Space && control->intersectBottomMario()){
        control->setIsJumping(true);
        control->setStartJumpY(control->getModel()->getMario()->getRect().y());
    }
    else if (event->key() == Qt::Key_Escape)
    {
        control->stopGame();
        qApp->exit();
    }
    else
        event->ignore();
}

//----------------------------------------------------------------------------------------------------------------//

void View::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right )
        control->setIsMovingR(false);
    else if(event->key() == Qt::Key_Left )
        control->setIsMovingL(false);
    else
        event->ignore();
}

void View::stopTimer(){
    killTimer(timerId);
}
