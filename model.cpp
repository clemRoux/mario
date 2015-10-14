#include "model.h"
#include "brick.h"
#include "gold.h"
#include <mario.h>
#include <safe.h>
#include <floor.h>
#include "darkeater.h"
#include <splashscreen.h>
#include <header.h>
#include <QDebug>

Model::Model()
{
    this->floors = new QMap<int,Floor *>;
    this->safes = new QMap<int,Safe *>;
    this->mushroom = new QMap<int,Mushroom *>;
    this->golds = new QMap<int,Gold *>;
    this->splashScreen = new SplashScreen(300, 100);
    this->background = new QMap<int,Background *>;
    this->header = new Header();
    this->compteur = new QMap<int, Brick*> ;
    this->mario = new Mario(200,340);

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
        Background* b = new Background(i*1000, 0);
        background->insert(backgroundCount, b);
        qDebug() << "create Background:" << backgroundCount;
        backgroundCount++;
    }
}

//--------------------------------------------------------------------------------------------------------//

Model::~Model()
{
    QMap< int,Floor *>::const_iterator i = floors->constBegin();
    QMap< int,Safe *>::const_iterator e = safes->constBegin();
    QMap< int,Brick *>::const_iterator c = compteur->constBegin();
    QMap<int,Background *>::const_iterator b= background ->constBegin();
    QMap<int, Mushroom *>::const_iterator m= mushroom ->constBegin();
    QMap<int, Gold*>::const_iterator g= golds ->constBegin();

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
    while (b != background->constEnd()) {
        delete  b.value();
        ++b;
    }
    while (m!= mushroom->constEnd()) {
        delete  m.value();
        ++m;
    }
    while (g!= golds->constEnd()) {
        delete  g.value();
        ++g;
    }
    floors->clear();
    delete floors;
    safes->clear();
    delete safes;
    compteur->clear();
    delete compteur;
    background->clear();
    delete background;
    mushroom->clear();
    delete mushroom;
    golds->clear();
    delete golds;
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
    case 3:{
        Gold* g= new Gold(NbrBrickVisible*brickSize,Hauteur-num*brickSize);
        golds->insert(goldCount,g);
        goldCount++;
        break;
    }
    case 4:{
        this->darkEater = new DarkEater(NbrBrickVisible*brickSize,Hauteur-num*brickSize);
        break;
    }
    case 5:{
        Mushroom* m = new Mushroom(NbrBrickVisible*brickSize,Hauteur-num*brickSize);
        this->mushroom->insert(mushroomCount, m);
        mushroomCount++;
        break;
    }
    case 6:{
        Safe* t= new Safe(NbrBrickVisible*brickSize,Hauteur-num*brickSize);
        t->setCapacity(2);
        safes->insert(safeCount,t);
        safeCount++;
        break;
    }
    }
}

//----------------------------------------------------------------------------------------------------------------//

void Model::brickOrganisation()
{
    QMutableMapIterator<int ,Background * > b0(*this->getBackground());
    QMutableMapIterator<int ,Brick * > c(*this->getCompteur());
    QMutableMapIterator<int ,Floor * > i(*this->getFloors());
    QMutableMapIterator<int ,Safe * > j(*this->getSafes());
    QMutableMapIterator<int ,Gold * > g(*this->getGold());
    QMutableMapIterator<int ,Mushroom * > m(*this->getMushroom());

    while (b0.hasNext()) {
        b0.next();
        if(b0.value()->getRect().x() < - b0.value()->getRect().width() + 2){
            b0.remove();
            Background* b = new Background(1000,0);
            background->insert( backgroundCount, b);
            qDebug() << "create Background:" << backgroundCount;
            backgroundCount++;
        }
    }
    while(c.hasNext()){
        c.next();
        if (c.value()->getRect().x()<=-brickSize){
            qDebug() << "Remove Compteur" << c.key() ;
            Brick *b=new Brick(c.value()->getRect().x()+(NbrBrickVisible)*brickSize,Hauteur+brickSize);
            c.remove();
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
            i.remove();
        }
    }

    while(j.hasNext()){
        j.next();
        if (j.value()->getRect().x()<=-brickSize || j.value()->isDestroyed()){
            j.remove();
        }
    }

    while(g.hasNext()){
        g.next();
        if (g.value()->getRect().x()<=-brickSize || g.value()->isDestroyed()){
            g.remove();
        }
    }

    while(m.hasNext()){
        m.next();
        if (m.value()->getRect().x()<=-brickSize || m.value()->isDestroyed()){
            m.remove();
        }
    }
}

void Model::createMushroom(int x, int y){
    Mushroom *m = new Mushroom(x+9, y+10);
    mushroom->insert(mushroomCount, m);
    mushroomCount++;
}


