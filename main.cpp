#include "gamefor2048.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gamefor2048 game;
    game.show();
    return a.exec();
}
