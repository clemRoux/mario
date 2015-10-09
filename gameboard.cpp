#include "gameboard.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include "model.h"


GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
{
    timerId = startTimer(10);
    this->model = new Model;
    gameStarted = true;
    moveL=false;
    moveR=false;
    isJumping=false;
    xRelatif = -100;
    yRelatif = 0;
    isSplashScreen = true;
    setIterBackground(0);
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

    QMap< int,Background *>::const_iterator b = model->getBackground()->constBegin();
    while (b != model->getBackground()->constEnd()) {
        painter.drawImage(b.value()->getRect(),b.value()->getImage());
        ++b;
    }


    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    QMap< int,Safe *>::const_iterator e = model->getSafes()->constBegin();
    QMap< int,Mushroom *>::const_iterator m = model->getMushroom()->constBegin();


    while (i != model->getFloors()->constEnd()) {
        painter.drawImage(i.value()->getRect(),i.value()->getImage());
        ++i;
    }
    while (e != model->getSafes()->constEnd()) {
        painter.drawImage(e.value()->getRect(),e.value()->getImage());
        ++e;
    }
    while (m != model->getMushroom()->constEnd()) {
        painter.drawImage(m.value()->getRect(),m.value()->getImage());
        ++m;
    }


    QRect sourceRect = QRect(currentFrame, 1, 57, 68);
    if(moveR){
        painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getMoveRSprite(), sourceRect);
    }
    else if(moveL){
        painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getMoveLSprite(), sourceRect);
    }
    else
        painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getStopSprite(), sourceRect);


    painter.drawImage(model->getHeader()->getRect().width() - 200, model->getHeader()->getRect().height() / 8, model->getHeader()->getGold());
    painter.setFont(QFont("Tahoma", 12, -1, false));
    QString goldText = "x" + QString::number(model->getMario()->getGoldNumber());
    painter.drawText(model->getHeader()->getGoldPosition(), goldText);

    for(int i = 0 ; i < model->getMario()->getLife() ; i++)
        painter.drawImage(model->getHeader()->getHeart().size().height() * i, 0, model->getHeader()->getHeart());

    if(isSplashScreen){
        opacity = opacity - 0.01;
        painter.setOpacity(opacity);
        painter.drawImage(model->getSplashScreen()->getRect(), model->getSplashScreen()->getImage());
    }
    else{
        opacity = 1;
        painter.setOpacity(opacity);
    }

    if(isHurted){
        opacity = opacity - 0.01;
        painter.setOpacity(opacity);
        qDebug() << "HURT!!";
        painter.drawPixmap(model->getMario()->getDieRect(), model->getMario()->getStopSprite(), QRect(0, 1, 57, 68));
    }
}

//-------------------------------------------------------------------------------------------------------------------//

void GameBoard::timerEvent(QTimerEvent *event)
{
    splashScreen();
    movementMario();
    hurted();
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

/*
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
    QMutableMapIterator<int ,Safe * > k(*model->getSafes());
    while (k.hasNext()) {
        k.next();
        if (k.value()->isDestroyed() ){
            qDebug() << "Remove Safe:" << k.key() ;
            k.remove();
        }
    }
    QMutableMapIterator<int ,Background * > b(*model->getBackground());
    while (b.hasNext()) {
        b.next();
        if (b.value()->isDestroyed() ){
            qDebug() << "Remove Background:" << b.key() ;
            b.remove();
        }
    }
}*/
//----------------------------------------------------------------------------------------------------------------//

void GameBoard::movementMario()
{
    int y=model->getMario()->getRect().y();
    int x=model->getMario()->getRect().x();

    if(isJumping && !intersectTopMario())
    {

        xRelatif+=4;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200);
        y = startJumpY-yRelatif;

        if(moveL && model->getMario()->getRect().x()>=2 && !intersectLeftMario())
            x-=4;
        else if(moveR && model->getMario()->getRect().x()<=240 && !intersectRightMario())
            x+=4;
        else if(moveR && model->getMario()->getRect().x()>=240 && !intersectRightMario())
            movementMap();
        model->getMario()->move(x,y);
    }

    if(intersectBottomMario() || intersectTopMario())
    {
        xRelatif=-100;
        yRelatif=0;
        isJumping=false;

        if(moveL && model->getMario()->getRect().x()>=2 && !intersectLeftMario())
            x-=4;
        else if(moveR && model->getMario()->getRect().x()<=240 && !intersectRightMario())
            x+=4;
        else if(moveR && model->getMario()->getRect().x()>=240 && !intersectRightMario())
            movementMap();

        model->getMario()->move(x, y);

        if(moveR && tempMove == 1){
            currentFrame += 57;
            if (currentFrame >= 1180 )
                currentFrame = 1;
            tempMove = 0;
        }
        else if(moveR)
            tempMove++;
        else if(moveL && tempMove == 1){
            currentFrame -= 57;
            if (currentFrame <= 0 )
                currentFrame = 1187;
            tempMove = 0;
        }
        else if(moveL)
            tempMove++;
        else
            currentFrame = 0;


    }

    if((!intersectBottomMario() && !isJumping )){
        y+=4;
        if(moveL && model->getMario()->getRect().x()>=2 && !intersectLeftMario() )
            x-=4;
        else if(moveR && model->getMario()->getRect().x()<=240  && !intersectRightMario())
            x+=4;
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

    QMap< int,Background *>::const_iterator k = model->getBackground()->constBegin();
    if(getIterBackground() == 4){
        while (k != model->getBackground()->constEnd()) {
            k.value()->moveBrick();
            ++k;
        }
        setIterBackground(0);
    }
    else{
        while (k != model->getBackground()->constEnd()) {
            k.value()->move(k.value()->getRect().x(), k.value()->getRect().y());
            ++k;
        }
        setIterBackground(getIterBackground() + 1);
    }

    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        j.value()->moveBrick();
        ++j;
    }
    QMap< int,Mushroom *>::const_iterator m = model->getMushroom()->constBegin();
    while (m != model->getMushroom()->constEnd()) {
        m.value()->moveBrick();
        ++m;
    }

    QMap< int,Brick *>::const_iterator s = model->getCompteur()->constBegin();
    while (s!= model->getCompteur()->constEnd()) {
        s.value()->moveBrick();
        ++s;
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

void GameBoard::splashScreen(){
    int x=model->getSplashScreen()->getRect().x();
    int y=model->getSplashScreen()->getRect().y();
    y = y - 2;
    if(model->getSplashScreen()->getRect().bottom() > 0 && isSplashScreen)
        model->getSplashScreen()->move(x, y);
    else
        isSplashScreen = false;
}


void GameBoard::hurted(){
    if(isHurted){
        if(opacity == 1)
            model->getMario()->setDieRect(QRect(model->getMario()->getRect().topLeft(), model->getMario()->getRect().bottomRight()));
        int x=model->getMario()->getDieRect().x();
        int y=model->getMario()->getDieRect().y();
        if(model->getMario()->getDieRect().bottom() > model->getMario()->getRect().top() + 20){
            y = y - 1;
            model->getMario()->moveDie(x, y);
        }
        else{
            isHurted = false;
            model->getMario()->setLife(model->getMario()->getLife() - 1);
        }
    }
}
