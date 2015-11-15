#include "model.h"
#include "brick.h"
#include "gold.h"
#include <mario.h>
#include <safe.h>
#include <floor.h>
#include "darkeater.h"
#include "blood.h"
#include <splashscreen.h>
#include <header.h>
#include "flame.h"
#include "shock.h"
#include "peach.h"
#include "encart.h"
#include <QDebug>

Model::Model()
{
    this->background = new QList<Background *>;
    this->floors = new QList<Floor *>;
    this->safes = new QList<Safe*>;
    this->mushroom = new QList<Mushroom *>;
    this->golds = new QList<Gold *>;
    this->flames = new QList<Flame *>;
    this->splashScreen = new SplashScreen(330, 170, ":images/go2.png");
    this->darkEater=new QList<DarkEater *>;
    this->background = new QList<Background *>;
    this->header = new Header();
    this->compteur = new QList<Brick*> ;
    this->mysticTrees = new QList<MysticTree *>;
    this->mario = new Mario(200, 340);
    this->blood = new Blood(0,0);
    this->shock = new Shock(0,0);
    this->encart = new Encart(0,0, "");
    getEncart()->setType(EncartType::NONE);

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
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne1.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEb")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne2.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEc")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne3.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEd")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne4.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEe")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne5.append(stock.at(i));
                    }
                }
            }
            else if (stock.left(6)=="LIGNEf")
            {
                for(int i=0;i<stock.size();++i){
                    if(stock.at(i).isDigit() || stock.at(i).isLetter()){
                        ligne6.append(stock.at(i));
                    }
                }
            }
        }
        fichier.close();
    }

    for (int i=0; i<NbrBrickVisible; i++) {
        Floor *k= new Floor(i*brickSize, Hauteur-brickSize, QString(":images/floor_bottom.jpg"));
        floors->append(k);
        Floor *k2= new Floor(i*brickSize, Hauteur-2*brickSize, QString(":images/floor_grass.png"));
        floors->append(k2);
    }
    for (int i=0; i<NbrBrickVisible; i++) {
        Brick *b=new Brick(i*brickSize,Hauteur+brickSize);
        compteur->append(b);
    }
    for (int i=0; i<2; i++) {
        Background* b = new Background(i*Model::Longueur, 0);
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
    darkEater->clear();
    delete darkEater;
    delete flames;
    golds->clear();
    delete golds;
    delete mario;
    delete splashScreen;
    mysticTrees->clear();
    delete mysticTrees;
}

//-----------------------------------------------------------------------------------------------------------------//

void Model::createBrick(QList<QChar> l ,int num ,int x){
    QChar myChar = l.at(mapPosition);

    if(myChar == '0')
        return;
    else if(myChar == '1'){
        Floor *k= new Floor(x+brickSize,Hauteur-num*brickSize, QString(":images/floor_bottom.jpg"));
        floors->append(k);
        return;
    }
    else if(myChar == '2'){
        Safe* t= new Safe(x+brickSize, Hauteur-num*brickSize);
        safes->append(t);
        return;
    }
    else if(myChar == '3'){
        Gold* g= new Gold(x+brickSize, Hauteur-num*brickSize);
        golds->append(g);
        return;
    }
    else if(myChar == '4'){
        DarkEater* d= new DarkEater(x+brickSize, Hauteur-num*brickSize);
        d->setMoveX(false);
        darkEater->append(d);
        return;
    }
    else if(myChar == '5'){
        Flame* f = new Flame(x+brickSize, Hauteur-num*brickSize);
        f->setMoveX(false);
        flames->append(f);
        return;
    }
    else if(myChar == '6'){
        Safe* t= new Safe(x+brickSize, Hauteur-num*brickSize);
        t->setCapacity(2);
        safes->append(t);
        return;
    }
    else if(myChar == '7'){
        Floor *k= new Floor(x+brickSize,Hauteur-num*brickSize , QString(":images/floor_grass.png"));
        floors->append(k);
        return;
    }
    else if(myChar == '8'){
        Floor *k= new Floor(x+brickSize,Hauteur-num*brickSize , QString(":images/floor_right.png"));
        floors->append(k);
        return;
    }
    else if(myChar == '9'){
        Floor *k= new Floor(x+brickSize,Hauteur-num*brickSize , QString(":images/floor_left.png"));
        floors->append(k);
        return;
    }  
    else if(myChar == 'a'){
        MysticTree *k= new MysticTree(x+brickSize,Hauteur-num*brickSize);
        mysticTrees->append(k);
        qDebug() << "Je Debug";
        return;
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
        }
    }
    if(compteur->last()->getRect().x()<((NbrBrickVisible)*brickSize)){
        Brick *b=new Brick(compteur->last()->getRect().x()+brickSize,Hauteur+brickSize);
        createBrick(ligne1,1,compteur->last()->getRect().x());
        createBrick(ligne2,2,compteur->last()->getRect().x());
        createBrick(ligne3,3,compteur->last()->getRect().x());
        createBrick(ligne4,4,compteur->last()->getRect().x());
        createBrick(ligne5,5,compteur->last()->getRect().x());
        createBrick(ligne6,6,compteur->last()->getRect().x());
        compteur->append(b);
        mapPosition++;
    }

    if (compteur->first()->getRect().x()<=-brickSize){
        compteur->removeAt(compteur->indexOf(compteur->first()));
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

    for(int i = 0; i<flames->size(); i++){
        if (flames->at(i)->getRect().x()<=-brickSize || flames->at(i)->isDestroyed()){
            flames->removeAt(i);
        }
    }

    for(int i = 0; i<darkEater->size(); i++){
        if (darkEater->at(i)->getRect().x()<=-brickSize ){
            darkEater->removeAt(i);
        }
    }
}

void Model::createMushroom(int x, int y, bool up){
    Mushroom *m = new Mushroom(x+9, y+10, up);
    m->setYR(0);
    m->setXR(0);
    m->setStartY(m->getRect().y() + 50);
    mushroom->append(m);
}

void Model::createGameOver(int x, int y){
    this->splashScreen = new SplashScreen(x, y, ":images/gameover.png");
}

void Model::createCompleted(int x, int y){
    this->splashScreen = new SplashScreen(x, y, ":images/level_complete.png");
}

void Model::createPeach(int x, int y){
    this->peach = new Peach(x, y);
    this->peach->setIsMovingL(true);
}

void Model::createEncart(int x, int y, QString image){
    this->encart = new Encart(x, y, image);
}
