#include "gameboard.h"
#include <QDesktopWidget>
#include <QApplication>
#include "model.h"
#include "view.h"

void center(QWidget &widget)
{
    int x, y;
    int screenWidth;
    int screenHeight;

    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - Model::Longueur) / 2;
    y = (screenHeight - Model::Hauteur) / 2;

    widget.setGeometry(x, y, Model::Longueur, Model::Hauteur);
    widget.setFixedSize(Model::Longueur, Model::Hauteur);
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Model m;
    View v;
    GameBoard window(&m, &v);
    v.setWindowTitle("Mario Game");
    v.show();
    center(v);
    return app.exec();
}
