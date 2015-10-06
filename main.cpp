#include "gameboard.h"
#include <QDesktopWidget>
#include <QApplication>
#include "model.h"

void center(QWidget &widget)
{
    int x, y;
    int screenWidth;
    int screenHeight;

    int WIDTH = 600;
    int HEIGHT = 500;

    QDesktopWidget *desktop = QApplication::desktop();

<<<<<<< HEAD
    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;

=======
    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;

>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
    widget.setGeometry(x, y, WIDTH, HEIGHT);
    widget.setFixedSize(WIDTH, HEIGHT);
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
<<<<<<< HEAD
    Model model;
    GameBoard window(&model, NULL);
    window.setWindowTitle("Mario Game");
    window.show();
    center(window);

=======
    GameBoard window;
    window.setWindowTitle("Mario Game");
    window.show();
    center(window);
>>>>>>> b7e12b5842d2b65c6d7c60266edb09301709941c
    return app.exec();
}
