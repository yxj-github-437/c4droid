#include "Board.h"
#include <QPainter>
#include<QWidget>
#include<QPushButton>
#include"Stone.h"
#include<QMouseEvent>


Board::Board(QWidget *parent):QWidget(parent)
{
    setFixedSize(1000,1200);
    setWindowTitle("象棋");
    QPushButton* Exit = new QPushButton("退出",this);
    Exit->move(400,1100);
    Exit->resize(200,50);
    connect(Exit,&QPushButton::clicked,this,&QWidget::close);

    for(int i=0;i<32;i++)
    {
        _s[i].init(i);
    }
}
void Board::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
 
    int d=100; 
    _r=d/2;//棋子半径

    //十条横线
    for(int i=1;i<=10;i++)
    {
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }
 
    //九条竖线
    for(int i=1;i<=9;i++)
    {
        if(i==1||i==9)
            painter.drawLine(QPoint(d*i,d),QPoint(i*d,10*d));
        else
        {
            painter.drawLine(QPoint(d*i,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(d*i,6*d),QPoint(i*d,10*d));
        }
    }
    //九宫格
    painter.drawLine(QPoint(d*4,d),QPoint(6*d,3*d));
    painter.drawLine(QPoint(d*6,d),QPoint(4*d,3*d));
 
    painter.drawLine(QPoint(d*4,10*d),QPoint(6*d,8*d));
    painter.drawLine(QPoint(d*6,10*d),QPoint(4*d,8*d));

     
    //绘制棋子
    for(int i=0;i<32;i++)
    {
        drawStone(painter,i);
    }
}

QPoint Board::center(int row,int col)
{
    QPoint ret;
    ret.rx()=(col+1)*_r*2;
    ret.ry()=(row+1)*_r*2;
    return ret;
}
QPoint Board::center(int id)
{
    return center(_s[id]._row,_s[id]._col);
}
 
void Board::drawStone(QPainter &painter,int id)
{
    if(_s[id]._dead)
        return;    
    QPoint c=center(id);
    QRect rect=QRect(c.rx()-_r,c.ry()-_r,_r*2,_r*2);
 
    if(id==_selectid)
        painter.setBrush(QBrush(Qt::gray));   //背景颜色
    else    
        painter.setBrush(QBrush(Qt::white));   //背景颜色
    painter.setPen(Qt::red);  //画红色矩形框
 
    if(_s[id]._black)
        painter.setPen(Qt::black);  //黑色棋子，默认的红色棋子
 
    painter.setFont(QFont("system", _r,700));  //字体
 
    painter.drawEllipse(center(id),_r,_r);
    painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));
}
bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    for(row=0; row<=9; row++)
    {
        for(col=0; col<=8; col++)
        {
            QPoint c = center(row, col);
            int dx = c.x() - pt.x();
            int dy = c.y() - pt.y();
            int dist = dx*dx+dy*dy;
            if(dist < _r*_r)
                return true;
        }
    }
    return false;
}
void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint pt=ev->pos();
    //将pt转化为棋子的行列值
    //然后再判断行列值上面有没有棋子
    int row,col;
    bool bRet = getRowCol(pt,row,col);
    if(bRet == false)   //点到棋盘外了
        return;
    int i;
    int clickid=-1;   //被点击的棋子
    for(i=0;i<32;i++)
    {
        if(_s[i]._row==row&&_s[i]._col==col&&_s[i]._dead == false)
        {
            break;
        }
    }
    if(i<32)  //棋子被选中
    {
        clickid=i;
    }
    if(canMove(_selectid,clickid)==false)
       return;
    if(_selectid==-1)
    {
        if(clickid!=-1)
        {
            _selectid=clickid;
            update();
        }
     }
    else
    {
        _s[_selectid]._row=row;
        _s[_selectid]._col=col;
        if(clickid!=-1)  //被点的地方如果有棋子就把他吃掉
            _s[clickid]._dead=true;
        _selectid=-1;
        update();
    }
 
}
bool Board::canMove(int moveid,int killid)
{
    if(_s[moveid]._black==_s[killid]._black)
        {_selectid=-1;
        update();
        return false;}
    return true;    
}
Board::~Board()
{
    
}