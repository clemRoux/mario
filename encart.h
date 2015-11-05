#ifndef ENCART_H
#define ENCART_H

#include "brick.h"
#include <QString>

enum struct EncartType {GOLD, LOVE, HURT, FUCK, NONE};

class Encart : public Brick
{
public:
    Encart(int, int, QString);
    ~Encart();
    void setShow(bool show){ this->show = show; }
    bool getShow(){ return show; }
    inline void setType(EncartType type){ this->type = type; }
    inline EncartType getType(){ return this->type; }

private:
    bool show = false;
    EncartType type;
};

#endif // ENCART_H
