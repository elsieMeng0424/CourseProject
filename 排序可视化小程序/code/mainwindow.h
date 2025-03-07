#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVector>
#include <QThread>
#include <windows.h>
#include <QThread>
#include "SortInfo.h"
#include "Array.h"
#include "Sorts.h"
#include "BarList.h"
#include "RecordList.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void wait();

private:
    Ui::MainWindow *ui;
    QPixmap inputMap; // 输入框的pixmap（输入框，排序选项按钮）
    QPixmap sortInfoMap; // 排序信息的pixmap
    QPixmap arrInfoMap; // 数组长度的pixmap
    QPixmap arrElemMap; // 数组元素的pixmap
    SortInfo* sortInfo; // 排序信息
    Array* arr; // 数组
    Array* arr_; // 用来复制的数组
    Array* arr_old; // 老数组
    Sorts* sorts; // 排序算法
    bool flag;

    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    //QVector<QGraphicsRectItem*> bars;
    BarList *bars; // 长方形链表
    QTimer *timer; // 计时器
    //QVector<int> record;
    recordList *record; // 记录链表（快速排序）
    int i = 1; // 计数器
    int j = 0; // 计数器
    int h = 1; // 计数器
    bool sorted = false; // 是否排序完成的判断标志

    void generateBars(); // 创建长方形对象并绘制
    void quickSort(int low, int height); // 快速排序的步骤
    void recordQuickSort(); // 记录快速排序（记录到record中）
    int part(int low, int height); // 快速排序的分组步骤

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_insertionBtn_clicked(); // 设置为直接插入排序
    void on_binaryBtn_clicked(); // 设置为折半插入排序
    void on_shellBtn_clicked(); // 设置为希尔排序
    void on_bubbleBtn_clicked(); // 设置为冒泡排序
    void on_quickBtn_clicked(); // 设置为快速排序
    void on_selectBtn_clicked(); // 设置为选择排序
    void on_randomInitBtn_clicked(); // 随机生成数组
    void on_setNumBtn_clicked(); // 设置数组长度
    void on_setElemBtn_clicked(); // 设置数组元素
    void on_sortBtn_clicked(); // 执行排序
    void on_resetBtn_clicked(); // 重置按钮

    void startSorting(); // 开始排序
    void insertionSortStep(); // 用于直接插入排序的槽函数
    void selectSortStep(); // 用于选择排序的槽函数
    void binaryInsertionSortStep(); // 用于折半插入排序的槽函数
    void bubbleSortStep(); // 用于冒泡排序的槽函数
    void shellSortStep(); // 用于希尔排序的槽函数
    void quickSortStep(); // 用于快速排序的槽函数
};

#endif // MAINWINDOW_H
