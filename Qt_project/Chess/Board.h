#ifndef BOARD_H
#define BOARD_H
 
#include <QWidget>
#include"Stone.h"
#include<QMouseEvent>
 
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    ~Board();
    Stone _s[32];
    int _r;//棋子半径
    int _selectid=-1;
 
    //返回棋盘对应的窗口坐标
    QPoint center(int row,int col);
    QPoint center(int id);
 
    void drawStone(QPainter &painter,int id);
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *ev);
    bool getRowCol(QPoint pt, int &row, int &col);
    bool canMove(int moveid,int killid);
 
signals:
 
public slots:
};
 
#endif // BOARD_H