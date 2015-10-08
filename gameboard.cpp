#include "gameboard.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include "model.h"


GameBoard::GameBoard(Model *model, QWidget *parent)
    : model(model), QWidget(parent)
{
    this->model = model;
    timerId = startTimer(10);
    gameStarted = true;
    moveL=false;
    moveR=false;
    isJumping=false;
    xRelatif = -100;
    yRelatif = 0;
    safeCount=0;
    moveCount=0;
    isSplashScreen = true;
    setIterBackground(0);
}

GameBoard::~GameBoard()
{
    killTimer(timerId);
}

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


    while (i != model->getFloors()->constEnd()) {
        painter.drawImage(i.value()->getRect(),i.value()->getImage());
        ++i;
    }
    while (e != model->getSafes()->constEnd()) {
        painter.drawImage(e.value()->getRect(),e.value()->getImage());
        ++e;
    }

    //painter.drawImage(model->getMario()->getRect(), model->getMario()->getImage());
    //painter.drawPixmap(200, 200, 400, 400, model->getMario()->getImageMap());

    QRect sourceRect = QRect(currentFrame, 2, 39, 70);
    painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getImageMap(), sourceRect);


    //painter.fillRect(model->getHeader()->getRect(), model->getHeader()->getColor());

    painter.drawImage(model->getHeader()->getRect().width() - 200, model->getHeader()->getRect().height() / 8, model->getHeader()->getGold());
    painter.setFont(QFont("Tahoma", 12, -1, false));
    QString goldText = "x" + QString::number(model->getMario()->getGoldNumber());
    //model->getMario()->getGoldNumber()
    painter.drawText(model->getHeader()->getGoldPosition(), goldText);

    for(int i = 0 ; i < model->getMario()->getLife() ; i++)
        painter.drawImage(model->getHeader()->getHeart().size().height() * i, 0, model->getHeader()->getHeart());

    if(isSplashScreen)
        painter.drawImage(model->getSplashScreen()->getRect(), model->getSplashScreen()->getImage());

}

void GameBoard::timerEvent(QTimerEvent *event)
{
    splashScreen();
    movementMario();
    removeDestroyed();
    repaint();
}


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
}

/*void GameBoard::movementBackground(){
    QPixmap bkgnd(":/images/background.png");
    QImage back = bkgnd.toImage();

    back.scaled(this->size(), Qt::IgnoreAspectRatio);
    if(back.size().width())
   //back.transformed()
    if(moveCount > 700/2){
        QPixmap bkgnd2(":/images/background.png");
        QImage back = bkgnd2.toImage();
        back = back.copy(moveCount/2, 0, 700, 700);
    }
    else{
        back = back.copy(moveCount/2, 0, 700, 700);
    }

    QPalette palette;
    palette.setBrush(QPalette::Background, back);
    this->setPalette(palette);
}*/


void GameBoard::movementMario()
{
    int y=model->getMario()->getRect().y();
    int x=model->getMario()->getRect().x();
    //Count type=move;
    //QList<QString> valuesList = model->getCount().values();
    if(isJumping)
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
            //movementBackground();
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
            //movementBackground();
            moveCount++;

        }
        model->getMario()->move(x, y);

        if(moveR && tempMove == 10){
            currentFrame += 90;
            if (currentFrame >= 810 )
                currentFrame = 2;
            tempMove = 0;
        }
        else if(moveR)
            tempMove++;
    }
    if(!intersect() && !isJumping){
        y = y + 2;
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

    QMap< int,Background *>::const_iterator k = model->getBackground()->constBegin();
    if(getIterBackground() == 4){
        while (k != model->getBackground()->constEnd()) {
            x0=k.value()->getRect().x();
            k.value()->moveBrick(x0-1);
            ++k;
        }
        setIterBackground(0);
    }
    else{
        while (k != model->getBackground()->constEnd()) {
            x0=k.value()->getRect().x();
            k.value()->moveBrick(x0);
            ++k;
        }
        setIterBackground(getIterBackground() + 1);
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

    QMap< int,Background *>::const_iterator b0= model->getBackground()->constBegin();
    while (b0 != model->getBackground()->constEnd()) {
        if(b0.value()->getRect().x() < - b0.value()->getRect().width() + 2){
            b0.value()->setDestroyed(true);
            Background* b = new Background(b0.value()->getRect().width(),0);
            model->getBackground()->insert(model->getBackgroundCount(), b);
            qDebug() << "create Background:" << model->getBackgroundCount() ;
            model->setBackgroundCount();
        }
        ++b0;
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

void GameBoard::splashScreen(){
    int x=model->getSplashScreen()->getRect().x();
    int y=model->getSplashScreen()->getRect().y();
    y--;
    if(model->getSplashScreen()->getRect().bottom() > 0 && isSplashScreen)
        model->getSplashScreen()->move(x, y);
    else
        isSplashScreen = false;
}
