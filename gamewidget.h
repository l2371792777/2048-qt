#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>

class gameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit gameWidget(QWidget *parent = nullptr);

signals:
    void ScoreUpdate(int);
    void KeyPressMove(int);

private:
    void paintEvent(QPaintEvent *);
    int board[4][4];
    int score;
    //是否有移动操作
    int isMove;
    //统计数字个数
    int digitCount;
    //延时出现新数字
    QTimer *timer;
    qreal w,h;
    qreal rX,rY;

    //初始化棋盘
    void init2Block();
    //键盘输入事件
    void keyPressEvent(QKeyEvent *);
    //获取数字进制
    int getBitCount(int);

    //todo
    //void isWin();
    //void isFailed();
public slots:
    void onKeyPressMove(int);
    void reStart();
};

#endif // GAMEWIDGET_H
