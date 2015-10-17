#ifndef HEADER_H
#define HEADER_H

#include <QRect>
#include <QColor>
#include <QString>
#include <QImage>

class Header
{
public:
    Header();
    QRect getRect(){ return rect; }
    QColor getColor(){ return color; }
    QString getText(){ return text; }
    QImage getHeart(){ return heart; }
    QRect getHeartSize(){ return heartSize; }
    QImage getGold(){ return gold; }
    QRect getGoldSize(){ return goldSize; }
    QPoint getGoldPosition(){ return goldPosition; }
private:
    QRect rect;
    QColor color;
    QString text;
    QImage heart;
    QImage gold;
    QRect heartSize;
    QRect goldSize;
    QPoint goldPosition;
};

#endif // HEADER_H
