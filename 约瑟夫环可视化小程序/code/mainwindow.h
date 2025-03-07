#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QVector>
#include <QTimer>
#include "Circle.h"
#include "Dice.h"
#include "PersonList.h"
#include "CircleList.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPixmap inputMap; // 输入map
    QPixmap infoMap; // 信息map

    Circle* circle; // 成员circle
    Dice* dice; // 骰子

    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QGraphicsView *diceView;
    QGraphicsScene *diceScene;
    //QVector<QGraphicsEllipseItem*> circles; // 代表成员的圆圈图形
    //QVector<QGraphicsEllipseItem*> spots; // 绘制骰子用的spot
    //QVector<Person*> personOut;
    CircleList* circles; // 圆圈链表
    CircleList* spots; // 骰子的小圈链表
    PersonList* personOut; // 出列的玩家链表
    QGraphicsRectItem* diceItem; // 正方形（骰子）
    QTimer *timer; // 计时器

    bool hasWinner = false; // 判断是否产生赢家

    int i; // 计数器
    Person* p;
    Person* q;

    void paintSpot(int n); // 绘制骰子的点数
    void generateCircle(); // 创建圆圈图案
    void onlyOneWarning(); // 只有一个玩家警告
    void noneWarning(); // 没有玩家警告


protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_addPersonBtn_clicked(); // 添加成员按钮
    void on_clearBtn_clicked(); // 清楚成员按钮
    void on_rollDiceBtn_clicked(); // 投骰子按钮
    void on_stepBtn_clicked(); // 进行一轮游戏按钮

    void step(); // 计数步骤的槽函数
};
#endif // MAINWINDOW_H
