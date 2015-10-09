#include "model.h"
#include "brick.h"
#include <mario.h>
#include <safe.h>
#include <floor.h>
#include <splashscreen.h>
#include <header.h>
#include <QDebug>

/*
 * if(moveCount==100){
        isHurted = true;
        qDebug() << "wtf ??";
        x0=650;
        y0=350;
        Mushroom* m =new Mushroom(x0,y0);
        model->getMushroom()->insert(model->getMushroomCount(), m);
        qDebug() << "create Mushroom:" << model->getMushroomCount() ;
        model->setMushroomCount();
    }
*/


Model::Model()
{
    this->floors = new QMap<int,Floor *>;
    this->safes = new QMap<int,Safe *>;
    this->mushroom = new QMap<int,Mushroom *>;
    this->splashScreen = new SplashScreen(100, 100);
    this->background = new QMap<int,Background *>;
    this->header = new Header();
    this->compteur = new QMap<int, Brick*> ;
    this->mario = new Mario(200,340);
    floorCount=0;
    safeCount=0;
    mapPosition=0;
    QFile fichier(":ModelMap.txt");

    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream in (&fichier);
        while(!in.atEnd())
        {
            QString stock = in.readLine();
            if (stock.left(6)=="LIGNEa")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit()){
                        ligne1.append(stock.at(i).digitValue());
                    }
                }
            }
            else if (stock.left(6)=="LIGNEb")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit()){
                        ligne2.append(stock.at(i).digitValue());
                    }
                }
            }
            else if (stock.left(6)=="LIGNEc")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit()){
                        ligne3.append(stock.at(i).digitValue());
                    }
                }
            }
            else if (stock.left(6)=="LIGNEd")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit()){
                        ligne4.append(stock.at(i).digitValue());
                    }
                }
            }
            else if (stock.left(6)=="LIGNEe")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit()){
                        ligne5.append(stock.at(i).digitValue());
                    }
                }
            }
        }
        fichier.close();
    }

    for (int i=0; i<NbrBrickVisible+1; i++) {
        for(int j=1; j<=2;j++){
            Floor *k= new Floor(i*brickSize,Hauteur-j*brickSize);
            floors->insert(floorCount,k);
            floorCount++;
        }
    }
    for (int i=0; i<NbrBrickVisible+1; i++) {
        Brick *b=new Brick(i*brickSize,Hauteur+brickSize);
        compteur->insert(mapPosition,b);
        mapPosition++;
    }
    for (int i=0; i<2; i++) {
        Background* b = new Background(i*800, 0);
        background->insert(backgroundCount, b);
        backgroundCount++;
    }
}

//--------------------------------------------------------------------------------------------------------//

Model::~Model()
{
    QMap< int,Floor *>::const_iterator i = floors->constBegin();
    QMap< int,Safe *>::const_iterator e = safes->constBegin();
    QMap< int,Brick *>::const_iterator c = compteur->constBegin();

    while (c != compteur->constEnd()) {
        delete c.value();
        ++c;
    }

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
    compteur->clear();
    delete compteur;
    delete mario;
    delete splashScreen;
}

//-----------------------------------------------------------------------------------------------------------------//

void Model::createBrick(QList<int> l ,int num )
{
    switch (l.at( mapPosition)) {
    case 0:
        break;
    case 1:{
        Floor *k= new Floor(NbrBrickVisible*brickSize,Hauteur-num*brickSize);
        floors->insert(floorCount,k);
        floorCount++;
        break;
    }
    case 2:{
        Safe* t= new Safe(NbrBrickVisible*brickSize,Hauteur-num*brickSize);
        safes->insert(safeCount,t);
        safeCount++;
        break;
    }
    }
}

//----------------------------------------------------------------------------------------------------------------//

void Model::brickOrganisation()
{
    QMap< int,Background *>::const_iterator b0= getBackground()->constBegin();
    while (b0 != getBackground()->constEnd()) {
        if(b0.value()->getRect().x() < - b0.value()->getRect().width() + 2){
            b0.value()->setDestroyed(true);
            Background* b = new Background(b0.value()->getRect().width(),0);
            getBackground()->insert(getBackgroundCount(), b);
            qDebug() << "create Background:" << getBackgroundCount() ;
            setBackgroundCount();
        }
        ++b0;
    }

    QMutableMapIterator<int ,Brick * > c(*this->getCompteur());
    QMutableMapIterator<int ,Floor * > i(*this->getFloors());
    QMutableMapIterator<int ,Safe * > j(*this->getSafes());
    while(c.hasNext()){
        c.next();
        if (c.value()->getRect().x()<=-brickSize){
            qDebug() << "Remove Compteur" << c.key() ;
            c.remove();
            Brick *b=new Brick(NbrBrickVisible*brickSize,Hauteur+brickSize);
            compteur->insert(mapPosition,b);
            createBrick(ligne1,1);
            createBrick(ligne2,2);
            createBrick(ligne3,3);
            createBrick(ligne4,4);
            createBrick(ligne5,5);
            mapPosition++;
        }
    }

    while(i.hasNext()){
        i.next();
        if (i.value()->getRect().x()<=-brickSize || i.value()->isDestroyed()){
            qDebug() << "Remove Floor:" << i.key() ;
            i.remove();
        }
    }

    while(j.hasNext()){
        j.next();
        if (j.value()->getRect().x()<=-brickSize || j.value()->isDestroyed()){
            qDebug() << "Remove Safe:" << j.key() ;
            j.remove();
        }
    }
}


