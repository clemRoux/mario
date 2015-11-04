#ifndef ENCART_H
#define ENCART_H

#include "brick.h"
#include <QString>

class Encart : public Brick
{
public:
    Encart(int, int, QString);
    ~Encart();
    void setShow(bool show){ this->show = show; }
    bool getShow(){ return show; }

private:
    bool show = false;
};

#endif // ENCART_H
