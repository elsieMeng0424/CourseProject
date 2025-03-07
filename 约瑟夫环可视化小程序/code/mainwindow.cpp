#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPainter>
#include <ctime>
#include <cmath>

#define Pi 3.14159265358979323846

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1500,900); // 设置整体画面大小
    setWindowTitle("Circle Game");

    inputMap = QPixmap(230,900); // 输入框
    infoMap = QPixmap(230, 900); // 信息框
    srand(time(0)); // 设置随机数种子

    circle = new Circle; // 新建圆圈类
    dice = new Dice; // 新建骰子类

    graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    graphicsView->setGeometry(250, 10, 1000, 880); // 设置主体动画显示栏

    diceView = new QGraphicsView(this);
    diceScene = new QGraphicsScene(this);
    diceView->setScene(diceScene);
    diceView->setGeometry(725, 250, 50,50);

    personOut = new PersonList; // 初始化出列玩家链表
    circles = new CircleList; // 初始化圆圈链表
    spots = new CircleList; // 初始化圆圈链表

    p = NULL;
    timer = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintSpot(int n)
{
    // 绘制骰子的信息
    // 根据骰子的值绘制对饮的点
    spots->clear();
    if(n == 1){
        QGraphicsEllipseItem* spot1 = diceScene->addEllipse(20, 20, 10, 10);
        spot1->setBrush(Qt::black);
        circleItem* c1 = new circleItem(spot1, NULL);
        spots->addCircle(c1);
    }
    else if(n == 2){
        QGraphicsEllipseItem* spot1 = diceScene->addEllipse(5, 5, 10, 10);
        spot1->setBrush(Qt::black);
        circleItem* c1 = new circleItem(spot1, NULL);
        spots->addCircle(c1);
        QGraphicsEllipseItem* spot2 = diceScene->addEllipse(35, 35, 10, 10);
        spot2->setBrush(Qt::black);
        circleItem* c2 = new circleItem(spot2, NULL);
        spots->addCircle(c2);
    }
    else if(n == 3){
        QGraphicsEllipseItem* spot1 = diceScene->addEllipse(20, 20, 10, 10);
        spot1->setBrush(Qt::black);
        circleItem* c1 = new circleItem(spot1, NULL);
        spots->addCircle(c1);
        QGraphicsEllipseItem* spot2 = diceScene->addEllipse(5, 5, 10, 10);
        spot2->setBrush(Qt::black);
        circleItem* c2= new circleItem(spot2, NULL);
        spots->addCircle(c2);
        QGraphicsEllipseItem* spot3 = diceScene->addEllipse(35, 35, 10, 10);
        spot3->setBrush(Qt::black);
        circleItem* c3 = new circleItem(spot3, NULL);
        spots->addCircle(c3);
    }
    else if(n == 4){
        QGraphicsEllipseItem* spot1 = diceScene->addEllipse(5, 5, 10, 10);
        spot1->setBrush(Qt::black);
        circleItem* c1 = new circleItem(spot1, NULL);
        spots->addCircle(c1);
        QGraphicsEllipseItem* spot2 = diceScene->addEllipse(35, 35, 10, 10);
        spot2->setBrush(Qt::black);
        circleItem* c2 = new circleItem(spot2, NULL);
        spots->addCircle(c2);
        QGraphicsEllipseItem* spot3 = diceScene->addEllipse(5, 35, 10, 10);
        spot3->setBrush(Qt::black);
        circleItem* c3 = new circleItem(spot3, NULL);
        spots->addCircle(c3);
        QGraphicsEllipseItem* spot4 = diceScene->addEllipse(35, 5, 10, 10);
        spot4->setBrush(Qt::black);
        circleItem* c4 = new circleItem(spot4, NULL);
        spots->addCircle(c4);
    }
    else if(n == 5){
        QGraphicsEllipseItem* spot1 = diceScene->addEllipse(20, 20, 10, 10);
        spot1->setBrush(Qt::black);
        circleItem* c1 = new circleItem(spot1, NULL);
        spots->addCircle(c1);
        QGraphicsEllipseItem* spot2 = diceScene->addEllipse(5, 5, 10, 10);
        spot2->setBrush(Qt::black);
        circleItem* c2 = new circleItem(spot2, NULL);
        spots->addCircle(c2);
        QGraphicsEllipseItem* spot3 = diceScene->addEllipse(35, 35, 10, 10);
        spot3->setBrush(Qt::black);
        circleItem* c3 = new circleItem(spot3, NULL);
        spots->addCircle(c3);
        QGraphicsEllipseItem* spot4 = diceScene->addEllipse(5, 35, 10, 10);
        spot4->setBrush(Qt::black);
        circleItem* c4 = new circleItem(spot4, NULL);
        spots->addCircle(c4);
        QGraphicsEllipseItem* spot5 = diceScene->addEllipse(35, 5, 10, 10);
        spot5->setBrush(Qt::black);
        circleItem* c5 = new circleItem(spot5, NULL);
        spots->addCircle(c5);
    }
    else if(n == 6){
        QGraphicsEllipseItem* spot1 = diceScene->addEllipse(5, 5, 10, 10);
        spot1->setBrush(Qt::black);
        circleItem* c1 = new circleItem(spot1, NULL);
        spots->addCircle(c1);
        QGraphicsEllipseItem* spot2 = diceScene->addEllipse(35, 35, 10, 10);
        spot2->setBrush(Qt::black);
        circleItem* c2 = new circleItem(spot2, NULL);
        spots->addCircle(c2);
        QGraphicsEllipseItem* spot3 = diceScene->addEllipse(5, 35, 10, 10);
        spot3->setBrush(Qt::black);
        circleItem* c3 = new circleItem(spot3, NULL);
        spots->addCircle(c3);
        QGraphicsEllipseItem* spot4 = diceScene->addEllipse(35, 5, 10, 10);
        spot4->setBrush(Qt::black);
        circleItem* c4 = new circleItem(spot4, NULL);
        spots->addCircle(c4);
        QGraphicsEllipseItem* spot5 = diceScene->addEllipse(20, 5, 10, 10);
        spot5->setBrush(Qt::black);
        circleItem* c5 = new circleItem(spot5, NULL);
        spots->addCircle(c5);
        QGraphicsEllipseItem* spot6 = diceScene->addEllipse(20, 35, 10, 10);
        spot6->setBrush(Qt::black);
        circleItem* c6 = new circleItem(spot6, NULL);
        spots->addCircle(c6);
    }
}

void MainWindow::generateCircle()
{
    // 创建圆圈图案
    scene->clear(); // 清空画布
    circles->clear(); // 清空圆圈链表
    int n = circle->getNum();
    if(n != 0){
        double angle = double(360) / n;
        int R = 400;
        int r = 10;
        // 根据数量不同设置半径
        if(n < 60)
            r = 20;
        if(n < 20)
            r = 30;
        if(n < 10)
            r = 35;
        if(n == 1)
            r = 50;
        double startAngle = 0;

        // 如果数量为1，将圆圈设置在中心
        if(n == 1){
            QGraphicsEllipseItem *c = scene->addEllipse(500-r,440-4,2*r,2*r);
            c->setBrush(QColor(167,204,237));
            circleItem *ci = new circleItem(c, NULL);
            circles->addCircle(ci);
        }
        else{
            // 绘制所有圆圈（根据角度计算位置）
            for(int i = 0; i < n; i++){
                int x = R * sin(startAngle*Pi/180), y = R * cos(startAngle*Pi/180);
                x += 500;
                y  = 440 - y;
                QGraphicsEllipseItem *c = scene->addEllipse(x-r,y-r,2*r,2*r);
                c->setBrush(QColor(167,204,237));
                circleItem *ci = new circleItem(c, NULL);
                circles->addCircle(ci);
                startAngle += angle;
            }
        }
    }
}

void MainWindow::onlyOneWarning()
{
    // 弹出警告框
    QMessageBox box;
    box.setWindowTitle("警告");
    box.setIcon(QMessageBox::Warning);
    box.setText("当前游戏人数仅有一人");
    QPushButton *yesBtn = box.addButton("是(&Y)", QMessageBox::YesRole);
    box.exec();
    if(box.clickedButton() == yesBtn)
        return;
}

void MainWindow::noneWarning()
{
    // 弹出警告框
    QMessageBox box;
    box.setWindowTitle("警告");
    box.setIcon(QMessageBox::Warning);
    box.setText("当前游戏没有玩家");
    QPushButton *yesBtn = box.addButton("是(&Y)", QMessageBox::YesRole);
    box.exec();
    if(box.clickedButton() == yesBtn)
        return;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(QColor(255,255,255));
    painter.drawRect(this->rect());

    // 绘制输入框
    QPainter inputPainter(&inputMap);
    QColor inputColor(84, 94, 117);
    inputPainter.setBrush(inputColor);
    inputPainter.drawRect(0,0,230,900);
    painter.drawPixmap(0,0,inputMap);

    // 绘制信息框
    QPainter infoPainter(&infoMap);
    infoPainter.setBrush(QColor(142,172,205));
    infoPainter.drawRect(0, 0, 230, 900);
    infoPainter.drawText(20, 50, "当前游戏人数：");
    infoPainter.drawText(130,50,QString::number(circle->getNum()));
    infoPainter.drawText(20,100,"出列的玩家：");
    infoPainter.drawText(20,70,"赢家为：");
    // 绘制赢家信息
    if(hasWinner){
        infoPainter.drawText(130, 70, QString::number(circle->getHead()->No));
        infoPainter.drawText(150, 70, QString::fromStdString(circle->getHead()->name));
    }
    int x = 20, y = 120;
    // 绘制出列的人的信息
    for(int i = 0; i < personOut->getNum(); i++){
        infoPainter.drawText(x, y, QString::number(personOut->getKth(i)->No));
        infoPainter.drawText(x+20, y, QString::fromStdString(personOut->getKth(i)->name));
        if(x != 120){
            x += 100;
        }
        else{
            x = 20;
            y += 20;
        }
    }
    //circle->paint(circleInfoPainter);
    dice->paint(infoPainter);
    painter.drawPixmap(1270, 0, infoMap);

}


void MainWindow::on_addPersonBtn_clicked()
{
    // 添加成员的按钮
    const QString name = ui->addPersonEdit->toPlainText();
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QApplication::restoreOverrideCursor();
    circle->addPerson(name);
    generateCircle();
    update(); // 更新画布
}


void MainWindow::on_clearBtn_clicked()
{
    if(!timer){
        // 清除所有成员
        p = NULL;
        hasWinner = false;
        circle->clear();
        personOut->clear();
        generateCircle();
        update(); // 更新画布
    }
}


void MainWindow::on_rollDiceBtn_clicked()
{
    // 投骰子
    diceScene->clear(); // 清楚scene
    //diceItem = diceScene->addRect(5,5,50,50); // 骰子的正方形主体
    dice->rollDice(); // 获取点数
    paintSpot(dice->getNum()); // 绘制骰子上的点
    update(); // 更新画布
}


void MainWindow::on_stepBtn_clicked()
{
    if(!timer){
        if(circle->getNum() == 0){
            noneWarning();
        }
        else{
            if(circle->getNum() != 1){
                timer = new QTimer(this);
                // 投骰子
                diceScene->clear();
                dice->rollDice();
                paintSpot(dice->getNum());
                update();

                i = 0;
                if(p == NULL)
                    p = circle->getHead();
                q = NULL;
                connect(timer, &QTimer::timeout, this, &MainWindow::step);
                timer->start(500);
            }
            else{
                onlyOneWarning();
            }
        }
    }
}

void MainWindow::step()
{
    if(i >= dice->getNum()){
        // 添加出列玩家
        Person* po = new Person(q->name,q->No,NULL);
        personOut->addPerson(po);

        // 删除出列玩家
        circle->DeletePerson(q);
        generateCircle();
        int startPos = circle->getPersonNum(p);
        circles->getKth(startPos)->item->setBrush(Qt::green);

        // 判断是否产生了赢家
        if(circle->getNum() == 1)
            hasWinner = true;
        update();

        timer->stop();
        timer = NULL;
        return;
    }

    if(i >= circle->getNum()){
        // 一轮过后颜色重新变为全部蓝色
        for(int m = 0; m < circles->getNum(); m++)
            circles->getKth(m)->item->setBrush(QColor(167,204,237));
    }
    int k = circle->getPersonNum(p);
    // 把点过的玩家变为红色
    circles->getKth(k)->item->setBrush(Qt::red);
    i++;
    q = p;
    p = p->next;
}

