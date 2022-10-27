#include <QAction>
#include <QMessageBox>

#include "gamefor2048.h"
#include "ui_gamefor2048.h"

gamefor2048::gamefor2048(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gamefor2048)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());

    //初始化游戏组件
    gamewidget=new gameWidget(this);
    gamewidget->setGeometry(10,85,300,300);
    connect(gamewidget,&gameWidget::ScoreUpdate,this,&gamefor2048::onScoreUpdate);
    connect(ui->btn_newgame,&QPushButton::clicked,gamewidget,&gameWidget::reStart);

}

gamefor2048::~gamefor2048()
{
    delete ui;
}

/**槽函数，更新分数显示
 * @brief gamefor2048::onScoreUpdate
 */
void gamefor2048::onScoreUpdate(int score)
{
    ui->view_score->setText(QString("Score:\n%1").arg(score));
}

