#ifndef GAMEFOR2048_H
#define GAMEFOR2048_H

#include <QMainWindow>
#include "gamewidget.h"

namespace Ui {
class gamefor2048;
}

class gamefor2048 : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamefor2048(QWidget *parent = nullptr);
    ~gamefor2048();

private:
    Ui::gamefor2048 *ui;
    gameWidget * gamewidget;

public slots:
    void onScoreUpdate(int);

};

#endif // GAMEFOR2048_H
