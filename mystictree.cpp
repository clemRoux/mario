#include "mystictree.h"



MysticTree::MysticTree(int x, int y) : Person(x,y)
{
    this->moveLSprite = QPixmap(":images/mysticTree.png");
    this->stopSprite = QPixmap(":images/mysticTree_die.png");
    this->rect = QRect(x, y, moveLSprite.width(), moveLSprite.height());
    this->isMovingL = true;
}
