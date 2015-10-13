#include "header.h"

Header::Header()
{
    this->rect = QRect(0, 0, 800, 40);
    this->color = QColor(Qt::white);
    this->text = QString("vie");
    this->heart = QImage();
    heart.load(":images/heart.png");
    this->heartSize = heart.rect();
    gold.load(":images/gold_small.png");
    this->goldSize = gold.rect();
    this->goldPosition = QPoint(this->getRect().width() - 70, this->getRect().height() - 15);
}
