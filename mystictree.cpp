#include "mystictree.h"



MysticTree::MysticTree(int x, int y) : Person(x,y)
{
    this->moveLSprite = QPixmap(":images/mysticTree.png");
    this->stopSprite = QPixmap(":images/mysticTree_die.png");
    this->rect = QRect(x, y, stopSprite.width(), stopSprite.height());
    this->isMovingL = true;
}
