#include "view.h"
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QRect>
#include <tuple>
#include "model.h"
#include "paintvisitor.h"

View::View(QWidget *parent): QWidget(parent)
{
    timerId = startTimer(15);
}

View::~View()
{
    killTimer(timerId);
    std::cout << ("View deleted\n");
}

void View::timerEvent(QTimerEvent *)
{
    update();
}

void View::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    PaintVisitor *pVisitor = new PaintVisitor(&painter);

    control->encart();
    control->splashScreen();
    control->movementMario();
    control->movementPeach();
    control->movementEncart();
    control->getModel()->brickOrganisation();
    control->goldAnim();
    control->intersectPeachMario();
    control->shockAnim();
    control->hurted();
    control->GameOver();
    control->Peach();

    for(int i = 0; i<control->getModel()->getCompteur()->size(); i++){
        if(control->getMoveMap())
            control->getModel()->getCompteur()->at(i)->moveBrick();
    }

    for(int i = 0; i<control->getModel()->getBackground()->size(); i++){
        if(control->getMoveMap())
            control->BackgroundAnim(i);
        control->getModel()->getBackground()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getMysticTrees()->size(); i++){
        if(control->getMoveMap())
            control->getModel()->getMysticTrees()->at(i)->move(control->getModel()->getMysticTrees()->at(i)->getRect().x() - Brick::speed, control->getModel()->getMysticTrees()->at(i)->getRect().y());
        control->movementMysticTree(i);
        control->getModel()->getMysticTrees()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getFloors()->size(); i++){
        if(control->getMoveMap())
            control->getModel()->getFloors()->at(i)->moveBrick();
        control->getModel()->getFloors()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getSafes()->size(); i++){
        if(control->getMoveMap())
            control->getModel()->getSafes()->at(i)->moveBrick();
        control->getModel()->getSafes()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getGold()->size(); i++){
        control->intersectGoldMario(i);
        if(control->getMoveMap())
           control->getModel()->getGold()->at(i)->moveBrick();
        control->getModel()->getGold()->at(i)->setSrcRect(QRect(Gold::currentFrame, 0, control->getModel()->getGold()->at(i)->getRect().width(), control->getModel()->getGold()->at(i)->getRect().height()));
        control->getModel()->getGold()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getMushroom()->size(); i++){
        control->intersectMushroomMario(i);
        control->movementMushroom(i);
        control->getModel()->getMushroom()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getFlame()->size(); i++){
        control->intersectFlameMario(i);
        control->flameAnim(i);
        control->getModel()->getFlame()->at(i)->accept(pVisitor);
    }

    for(int i = 0; i<control->getModel()->getDarkEater()->size(); i++){
        if(control->getModel()->getDarkEater()->at(i)->isDestroyed() && control->getMoveMap())
            control->getModel()->getDarkEater()->at(i)->moveBrick();
        control->darkeaterAnim(i);
        control->getModel()->getDarkEater()->at(i)->accept(pVisitor);
    }

    if(control->getModel()->getShock()->getShow()){
        control->getModel()->getShock()->setSrcRect(QRect(0, Shock::currentFrame, control->getModel()->getShock()->getRect().width(), control->getModel()->getShock()->getRect().height()));
        control->getModel()->getShock()->accept(pVisitor);
    }

    if(control->getModel()->getMario()->getIsLittle()){
        control->getModel()->getMario()->setRect(QRect(control->getModel()->getMario()->getRect().x(), control->getModel()->getMario()->getRect().y(), 25, control->getModel()->getMario()->getMoveRSprite().height() - 30));
        control->getModel()->getMario()->setSrcRect(QRect(control->getModel()->getMario()->getCurrentFrame()+6, 0, control->getModel()->getMario()->getRect().width()+25, control->getModel()->getMario()->getRect().height()+27));
    }
    else{
        control->getModel()->getMario()->setRect(QRect(control->getModel()->getMario()->getRect().x(), control->getModel()->getMario()->getRect().y(), 45, control->getModel()->getMario()->getMoveRSprite().height() - 7));
        control->getModel()->getMario()->setSrcRect(QRect(control->getModel()->getMario()->getCurrentFrame()+6, 1, control->getModel()->getMario()->getRect().width(), control->getModel()->getMario()->getRect().height()));
    }

    if(control->getModel()->getIsPeachBool()){
        if(control->getModel()->getIsPeachBool() && control->getMoveMap())
            control->getModel()->getPeach()->move(control->getModel()->getPeach()->getRect().x() - Brick::speed, control->getModel()->getPeach()->getRect().y());
        control->getModel()->getPeach()->setRect(QRect(control->getModel()->getPeach()->getRect().x(), control->getModel()->getPeach()->getRect().y(), control->getModel()->getPeach()->getMoveLSprite().width() / 4, control->getModel()->getPeach()->getMoveLSprite().height()));
        control->getModel()->getPeach()->setSrcRect(QRect(control->getModel()->getPeach()->getCurrentFrame(), 0, control->getModel()->getPeach()->getRect().width(), control->getModel()->getPeach()->getRect().height() + 4));
        control->getModel()->getPeach()->accept(pVisitor);
    }

    control->getModel()->getMario()->accept(pVisitor);

    if(control->getModel()->getEncart()->getShow())
        control->getModel()->getEncart()->accept(pVisitor);

    painter.drawImage(control->getModel()->getHeader()->getRect().width() - 0, control->getModel()->getHeader()->getRect().height() / 8, control->getModel()->getHeader()->getGold());
    painter.setFont(QFont("Tahoma", 17, 0, true));
    QString goldText = QString::number(control->getModel()->getMario()->getGoldNumber());
    painter.drawText(control->getModel()->getHeader()->getGoldPosition(), goldText);

    painter.save();
    if(control->getModel()->getMario()->getUntouchable())
        painter.setOpacity(0.4);
    else
        painter.setOpacity(1);

    for(int i = 0 ; i < control->getModel()->getMario()->getLife() ; i++){
        painter.drawImage(control->getModel()->getHeader()->getHeart().size().height() * i, 0, control->getModel()->getHeader()->getHeart());
    }
    painter.restore();

    if(!control->getModel()->getBlood()->getStopBlood() && control->getModel()->getMario()->getIsHurted()){ // Paint Blood when hurted
        control->getModel()->getBlood()->accept(pVisitor);
    }

    if(control->GameOver()){
        painter.fillRect(QRect(0, 0, Model::Longueur, Model::Hauteur), QBrush(QColor(128, 128, 255, 230)));
    }
    else if(control->Completed())
        painter.fillRect(QRect(0, 0, Model::Longueur, Model::Hauteur), QBrush(QColor(29, 153, 215, 230)));

    if(control->getModel()->getSplashScreen()->getIsSplashScreen()){
        control->getModel()->getSplashScreen()->accept(pVisitor);
    }
}

//-------------------------------------------------------------------------------------------------------------------//

void View::keyPressEvent(QKeyEvent *event)
{
    if(!control->GameOver()){
        if(event->key() == Qt::Key_Right)
            control->setIsMovingR(true);
        else if(event->key() == Qt::Key_Left)
            control->setIsMovingL(true);
        else if(event->key() == Qt::Key_Down && control->getIsJumping())
            control->setIsAttacking(true);
        else if(event->key() == Qt::Key_Space && control->intersectBottomMario()){
            control->setIsJumping(true);
            control->setXRelatif(-100);
        }
        else
            event->ignore();
    }
    else if(event->key() == Qt::Key_Enter){

    }

    if (event->key() == Qt::Key_Escape)
    {
        control->stopGame();
        qApp->exit();
    }

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
