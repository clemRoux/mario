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
    this->background = new QList<Background *>;
    this->floors = new QList<Floor *>;
    this->safes = new QList<Safe*>;
    this->mushroom = new QList<Mushroom *>;
    this->golds = new QList<Gold *>;
    this->splashScreen = new SplashScreen(300, 100);
    this->background = new QList<Background *>;
    this->header = new Header();
    this->compteur = new QList<Brick*> ;
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
            floors->append(k);
        }
    }
    for (int i=0; i<NbrBrickVisible+1; i++) {
        Brick *b=new Brick(i*brickSize,Hauteur+brickSize);
        compteur->append(b);
    }
    for (int i=0; i<2; i++) {
        Background* b = new Background(i*1000, 0);
        background->append(b);
    }
}

//--------------------------------------------------------------------------------------------------------//

Model::~Model()
{
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
        floors->append(k);
        break;
    }
    case 2:{
        Safe* t= new Safe(NbrBrickVisible*brickSize,Hauteur-num*brickSize);
        safes->append(t);
        break;
    }
    case 3:{
        Gold* g= new Gold(NbrBrickVisible*brickSize,Hauteur-num*brickSize);
        golds->append(g);
        break;
    }
    case 4:{
        this->darkEater = new DarkEater(NbrBrickVisible*brickSize,Hauteur-num*brickSize);
        break;
    }
    case 6:{
        Safe* t= new Safe(NbrBrickVisible*brickSize,Hauteur-num*brickSize);
        t->setCapacity(2);
        safes->append(t);
        break;
    }
    }
}

//----------------------------------------------------------------------------------------------------------------//

void Model::brickOrganisation()
{
    for(int i = 0; i<background->size(); i++){
        if(background->at(i)->getRect().x() < - background->at(i)->getRect().width() + 2){
            background->removeAt(i);
            Background* b = new Background(1000,0);
            background->append(b);
            qDebug() << "create Background:";
        }
    }

    for(int i = 0; i<compteur->size(); i++){
        if (compteur->at(i)->getRect().x()<=-brickSize){
            compteur->removeAt(i);
            Brick *b=new Brick(compteur->at(i)->getRect().x()+(NbrBrickVisible)*brickSize,Hauteur+brickSize);
            compteur->append(b);
            createBrick(ligne1,1);
            createBrick(ligne2,2);
            createBrick(ligne3,3);
            createBrick(ligne4,4);
            createBrick(ligne5,5);
            mapPosition++;
        }
    }

    for(int i = 0; i<floors->size(); i++){
        if (floors->at(i)->getRect().x()<=-brickSize || floors->at(i)->isDestroyed()){
            floors->removeAt(i);
        }
    }

    for(int i = 0; i<safes->size(); i++){
        if (safes->at(i)->getRect().x()<=-brickSize || safes->at(i)->isDestroyed()){
            safes->removeAt(i);
        }
    }

    for(int i = 0; i<golds->size(); i++){
        if (golds->at(i)->getRect().x()<=-brickSize || golds->at(i)->isDestroyed()){
            golds->removeAt(i);
        }
    }

    for(int i = 0; i<mushroom->size(); i++){
        if (mushroom->at(i)->getRect().x()<=-brickSize || mushroom->at(i)->isDestroyed()){
            mushroom->removeAt(i);
        }
    }

    if(darkEater->isDead())
        delete darkEater;
}

void Model::createMushroom(int x, int y){
    Mushroom *m = new Mushroom(x+9, y+10);
    mushroom->append(m);
}


