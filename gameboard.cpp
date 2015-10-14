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
    iterBackground=0;
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
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    QMap< int,Safe *>::const_iterator e = model->getSafes()->constBegin();
    QMap< int,Mushroom *>::const_iterator m = model->getMushroom()->constBegin();
    QMap< int,Gold *>::const_iterator g = model->getGold()->constBegin();

    while (b != model->getBackground()->constEnd()) {
        painter.drawImage(b.value()->getRect(),b.value()->getImage());
        ++b;
    }
    while (i != model->getFloors()->constEnd()) {
        painter.drawImage(i.value()->getRect(),i.value()->getImage());
        ++i;
    }
    while (e != model->getSafes()->constEnd()) {
        if(e.value()->getCapacity()==1)
            e.value()->setImage(":images/floor_uni.png");
        painter.drawImage(e.value()->getRect(),e.value()->getImage());
        ++e;
    }
    while (m != model->getMushroom()->constEnd()) {
        painter.drawImage(m.value()->getRect(),m.value()->getImage());
        ++m;
    }
    while (g != model->getGold()->constEnd()) {
        QRect srcRect = QRect(currentGoldFrame, 0, g.value()->getRect().width(), g.value()->getRect().height());
        painter.drawPixmap(g.value()->getRect(), g.value()->getSprite(), srcRect);
        ++g;
    }
    if(model->getDarkEater() != NULL){
        QRect srcRect = QRect(currentDarkEaterFrame, 0, model->getDarkEater()->getRect().width(), model->getDarkEater()->getRect().height());
        painter.drawPixmap(model->getDarkEater()->getRect(), model->getDarkEater()->getMoveLSprite(), srcRect);
    }


    QRect sourceRect = QRect(currentFrame+6, 1, model->getMario()->getRect().width(), model->getMario()->getRect().height()+3);
    if(moveR){
        painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getMoveRSprite(), sourceRect);
    }
    else if(moveL){
        painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getMoveLSprite(), sourceRect);
    }
    else
        painter.drawPixmap(model->getMario()->getRect() ,model->getMario()->getStopSprite(), sourceRect);

    painter.drawImage(model->getHeader()->getRect().width() - 100, model->getHeader()->getRect().height() / 8, model->getHeader()->getGold());
    painter.setFont(QFont("Tahoma", 12, -1, false));
    QString goldText = "x" + QString::number(model->getMario()->getGoldNumber());
    painter.drawText(model->getHeader()->getGoldPosition(), goldText);

    for(int i = 0 ; i < model->getMario()->getLife() ; i++)
        painter.drawImage(model->getHeader()->getHeart().size().height() * i, 0, model->getHeader()->getHeart());

    if(isSplashScreen){
        opacity = opacity - 0.005;
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
    movementMushroom();
    movementDarkEater();
    hurted();
    model->brickOrganisation();
    goldAnim();
    repaint();
}

//----------------------------------------------------------------------------------------------------------------//

void GameBoard::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right)
        moveR=true;
    else if(event->key() == Qt::Key_Left)
        moveL=true;
    else if(event->key() == Qt::Key_Space && intersectBottomMario()){
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
        moveR=false;
    else if(event->key() == Qt::Key_Left )
        moveL=false;
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
    if(isJumping && !intersectTopMario()){
        xRelatif+=3;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200);
        y = startJumpY-yRelatif;
        moveXMario(y);
        currentFrame = 0;
    }
    if(intersectBottomMario() || intersectTopMario()){
        xRelatif=-100;
        yRelatif=0;
        isJumping=false;
        moveXMario(y);
        if(moveR && tempMove == 1){
            currentFrame += 57;
            if (currentFrame >= 1190 )
                currentFrame = 1;
            tempMove = 0;
        }
        else if(moveR)
            tempMove++;
        else if(moveL && tempMove == 1){
            currentFrame -= 57;
            if (currentFrame <= 0 )
                currentFrame = 1191;
            tempMove = 0;
        }
        else if(moveL)
            tempMove++;
        else
            currentFrame = 0;
    }
    if((!intersectBottomMario() && !isJumping )){
        y += 3;
        moveXMario(y);
        currentFrame = 0;
    }
    intersectGoldMario();
    intersectMushroomMario();
}

void GameBoard::movementDarkEater()
{
    if(model->getDarkEater() != NULL){
        model->getDarkEater()->move(model->getDarkEater()->getRect().x() - 2, model->getDarkEater()->getRect().y());
        if(darkEaterTempo == 10){
            currentDarkEaterFrame += 104;
            if (currentDarkEaterFrame >= 312 )
                currentDarkEaterFrame = 1;
            darkEaterTempo = 0;
        }
        else
            darkEaterTempo++;
    }
}
//----------------------------------------------------------------------------------------------------------------//

void GameBoard::moveXMario(int y)
{
    int x=model->getMario()->getRect().x();
    if(moveL && model->getMario()->getRect().x()>=2 && !intersectLeftMario() )
        x-=2;
    else if(moveR && model->getMario()->getRect().x()<=350  && !intersectRightMario())
        x+=2;
    else if(moveR && model->getMario()->getRect().x()>=350  && !intersectRightMario())
        movementMap();
    model->getMario()->move(x,y);
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
    if(iterBackground== 4){
        while (k != model->getBackground()->constEnd()) {
            k.value()->moveBrick();
            ++k;
        }
        iterBackground=0;
    }
    else{
        while (k != model->getBackground()->constEnd()) {
            k.value()->move(k.value()->getRect().x(), k.value()->getRect().y());
            ++k;
        }
        iterBackground++;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        j.value()->moveBrick();
        ++j;
    }
    QMap< int,Brick *>::const_iterator s = model->getCompteur()->constBegin();
    while (s!= model->getCompteur()->constEnd()) {
        s.value()->moveBrick();
        ++s;
    }
    QMap< int,Gold *>::const_iterator g = model->getGold()->constBegin();
    while (g!= model->getGold()->constEnd()) {
        g.value()->moveBrick();
          ++g;
    }
}

//----------------------------------------------------------------------------------------------------------------//

bool GameBoard::intersectTopMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        if(model->getMario()->intersectTop(i.value()->getRect()))
            return true;
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(model->getMario()->intersectTop(j.value()->getRect())){
            if(j.value()->getCapacity()){
                if(j.value()->getCapacity() == 2){
                    model->createMushroom(j.value()->getRect().x(), j.value()->getRect().y());
                    j.value()->setCapacity(1);
                }
            }else
                j.value()->setDestroyed(true);
            return true;
        }
        ++j;
    }
    return false;
}

bool GameBoard::intersectBottomMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()){
        if(model->getMario()->intersectBottom(i.value()->getRect()))
            return true;
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(model->getMario()->intersectBottom(j.value()->getRect()))
            return true;
        ++j;
    }
    return false;
}

bool GameBoard::intersectLeftMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        if(model->getMario()->intersectLeft(i.value()->getRect()))
            return true;
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(model->getMario()->intersectLeft(j.value()->getRect()))
            return true;
        ++j;
    }
    return false;
}

bool GameBoard::intersectRightMario()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        if(model->getMario()->intersectRight(i.value()->getRect()))
            return true;
        ++i;
    }
    QMap< int,Safe *>::const_iterator j = model->getSafes()->constBegin();
    while (j != model->getSafes()->constEnd()) {
        if(model->getMario()->intersectRight(j.value()->getRect()))
            return true;
        ++j;
    }
    return false;
}

void GameBoard::intersectGoldMario()
{
    QMap< int,Gold *>::const_iterator j = model->getGold()->constBegin();
    while (j != model->getGold()->constEnd()) {
        if(model->getMario()->intersect(j.value()->getRect())){
            j.value()->setDestroyed(true);
            model->getMario()->setGoldNumber(model->getMario()->getGoldNumber()+1);}
        ++j;
    }
}

void GameBoard::intersectMushroomMario()
{
    QMap< int,Mushroom *>::const_iterator j = model->getMushroom()->constBegin();
    while (j != model->getMushroom()->constEnd()) {
        if(model->getMario()->intersect(j.value()->getRect())){
            j.value()->setDestroyed(true);
        }
        ++j;
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void GameBoard::splashScreen(){
    int x=model->getSplashScreen()->getRect().x();
    int y=model->getSplashScreen()->getRect().y();
    y--;
    if(model->getSplashScreen()->getRect().bottom() > 0 && isSplashScreen)
        model->getSplashScreen()->move(x, y);
    else
        isSplashScreen = false;
}

//-----------------------------------------------------------------------------------------------------------------------//

void GameBoard::goldAnim(){
    if(temp == 20){
        currentGoldFrame += 40;
        if (currentGoldFrame >= 120 )
            currentGoldFrame = 0;
        temp = 0;
    }
    else
        temp++;
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

void GameBoard::movementMushroom(){
    QMap< int,Mushroom *>::const_iterator m = model->getMushroom()->constBegin();
    while (m != model->getMushroom()->constEnd()) {
        if(m.value()->getMoveCount()>0){
            m.value()->setmoveCount(m.value()->getMoveCount() - 1);
            if(moveR && model->getMario()->getRect().x()>=350  && !intersectRightMario())
                m.value()->move(m.value()->getRect().x() - 2, m.value()->getRect().y() - 1);
            else
                m.value()->move(m.value()->getRect().x(), m.value()->getRect().y() - 1);
        }
        else if(moveR && model->getMario()->getRect().x()>=350  && !intersectRightMario()){
            m.value()->move(m.value()->getRect().x() - 2, m.value()->getRect().y());
        }
        ++m;
    }
}
