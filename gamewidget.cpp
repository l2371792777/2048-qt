#include "gamewidget.h"

// 颜色数组 存储每个数字对应的背景色
QColor digitBkg[12] = {QColor::fromRgb(171, 165, 141),
                       QColor::fromRgb(0xFF, 0xFF, 0xCC), QColor::fromRgb(0xFF, 0xFF, 0x99),
                       QColor::fromRgb(0xFF, 0xCC, 0xCC), QColor::fromRgb(0xFF, 0xCC, 0x99),
                       QColor::fromRgb(0xFF, 0x99, 0x99), QColor::fromRgb(0xFF, 0x99, 0x66),
                       QColor::fromRgb(0xFF, 0x66, 0x66), QColor::fromRgb(0xCC, 0x99, 0x66),
                       QColor::fromRgb(0xCC, 0x33, 0x33), QColor::fromRgb(0xCC, 0x00, 0x33),
                       QColor::fromRgb(0xFF, 0x00, 0x00)};

gameWidget::gameWidget(QWidget *parent)
    : QWidget{parent}
{
    timer=new QTimer();
    //初始化界面
    reStart();
    this->grabKeyboard();
    connect(this,&gameWidget::KeyPressMove,this,&gameWidget::onKeyPressMove);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
}

void gameWidget::init2Block()
{
    //生成两个数字
    board[rand()%4][rand()%4]=2;
    int i=rand()%4,j=rand()%4;
    while(board[i][j]!=0)
        i=rand()%4,j=rand()%4;
    board[i][j]=2;
    digitCount+=2;
    update();
}

/** 键盘输入事件
 * @brief gameWidget::keyPressEvent
 * @param e
 */
void gameWidget::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_W:
    case Qt::Key_A:
    case Qt::Key_S:
    case Qt::Key_D:
        emit KeyPressMove(e->key());
        break;
    }
}

/** 移动数字
 * @brief gameWidget::onKeyPressMove
 */
void gameWidget::onKeyPressMove(int keyPress)
{
    int i,j,k;
    //该位置是否合并过
    bool isCombined[4][4];
    memset(isCombined,0,sizeof(isCombined));
    isMove=0;
    switch(keyPress)
    {
    //上移
    case Qt::Key_W:
        //遍历每列
        for(j=0;j<4;j++)
        {
            i=0,k=0;
            while(true){
                //找到第一个有数字的位置
                while(i<4&&board[i][j]==0)
                    i++;
                if(i>3)
                    break;
                //找到可以转移得位置
                while(k<i&&board[k][j]!=0)
                    k++;
                //交换位置
                qSwap(board[i][j],board[k][j]);
                if(i==k)
                    i++;
                else
                    isMove++;
                //如果和前一个位置数字相同，合并两个数字
                if(k>0&&board[k][j]==board[k-1][j]&&!isCombined[k-1][j])
                {
                    board[k-1][j]=2*board[k-1][j];
                    board[k][j]=0;
                    score+=board[k-1][j];
                    digitCount-=1;
                    isCombined[k-1][j]=1,isMove++;
                }
            }
        }
        break;
    case Qt::Key_S:
        for(j=0;j<4;j++)
        {
            i=3,k=3;
            while(true){
                while(i>=0&&board[i][j]==0)
                    i--;
                if(i<0)
                    break;
                while(k>i&&board[k][j]!=0)
                    k--;
                qSwap(board[i][j],board[k][j]);
                if(i==k)
                    i--;
                else
                    isMove++;
                if(k<3&&board[k][j]==board[k+1][j]&&!isCombined[k+1][j])
                {
                    board[k+1][j]=2*board[k+1][j];
                    board[k][j]=0;
                    score+=board[k+1][j];
                    digitCount-=1;
                    isCombined[k+1][j]=1,isMove++;
                }
            }
        }
        break;
    case Qt::Key_A:
        for(i=0;i<4;i++)
        {
            j=0,k=0;
            while(true){
                while(j<4&&board[i][j]==0)
                    j++;
                if(j>3)
                    break;
                while(k<j&&board[i][k]!=0)
                    k++;
                qSwap(board[i][k],board[i][j]);
                if(j==k)
                    j++;
                else
                    isMove++;
                if(k>0&&board[i][k]==board[i][k-1]&&!isCombined[i][k-1])
                {
                    board[i][k-1]=2*board[i][k-1];
                    board[i][k]=0;
                    score+=board[i][k-1];
                    digitCount-=1;
                    isCombined[i][k-1]=1,isMove++;
                }
            }
        }
        break;
    case Qt::Key_D:
        for(i=0;i<4;i++)
        {
            j=3,k=3;
            while(true){
                while(j>=0&&board[i][j]==0)
                    j--;
                if(j<0)
                    break;
                while(k>j&&board[i][k]!=0)
                    k--;
                qSwap(board[i][k],board[i][j]);
                if(j==k)
                    j--;
                else
                    isMove++;
                if(k<3&&board[i][k]==board[i][k+1]&&!isCombined[i][k+1])
                {
                    board[i][k+1]=2*board[i][k+1];
                    board[i][k]=0;
                    score+=board[i][k+1];
                    digitCount-=1;
                    isCombined[i][k+1]=1,isMove++;
                }
            }
        }
        break;
    }
    //更新数据
    update();
    emit ScoreUpdate(score);

    if(isMove&&digitCount!=16)
    {
        //生成新的数字
        i=rand()%4,j=rand()%4;
        while(board[i][j]!=0)
        i=rand()%4,j=rand()%4;
        board[i][j]=2;
        digitCount+=1;
    }
    timer->start(1000);
}

int gameWidget::getBitCount(int digit)
{
    int i=0;
    while(digit!=0)
        digit=digit/2,i++;
    return i;
}

/** 绘画事件
 * @brief gameWidget::paintEvent
 */
void gameWidget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush(QColor::fromRgb(141,121,81));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(QRectF(0,0,300,300),0,0);

    //设置字体
    QFont font;
    font.setFamily("consolas");
    font.setBold(true);
    font.setPixelSize(40);
    painter.setFont(font);

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(board[i][j])
            {
                //绘制方格
                brush.setColor(digitBkg[getBitCount(board[i][j])]);
                painter.setBrush(brush);
                painter.drawRoundedRect(QRectF(4*(j+1)+h*j,4*(i+1)+w*i,w,h),rX,rY);
                //绘制数字
                painter.setPen(QColor::fromRgb(0,0,0));
                painter.drawText(QRectF(4*(j+1)+h*j,4*(i+1)+w*i,w,h),Qt::AlignCenter,QString("%1").arg(board[i][j]));
                painter.setPen(Qt::NoPen);
            }
            else
            {
                brush.setColor(digitBkg[0]);
                painter.setBrush(brush);
                painter.drawRoundedRect(QRectF(4*(j+1)+h*j,4*(i+1)+w*i,w,h),rX,rY);
            }

        }
    }

}

/** 重设数据
 * @brief gameWidget::reStart
 */
void gameWidget::reStart()
{
    //小方块长、宽
    w=70,h=70;
    //初始化数组
    //初始化数据
    memset(board,0,sizeof(board));
    //生成两个数字
    init2Block();
    update();
    digitCount=0;
    score=0;
    emit ScoreUpdate(score);
}
