#ifndef __SORTS_H__
#define __SORTS_H__

#include "Array.h"
#include "tools.h"
#include "SortInfo.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVector>
#include <QThread>
#include <QMainWindow>
#include <QTimer>

// 排序类
class Sorts {
public:
    Sorts();
    void sort(SortInfo info, Array arr); // 排序（根据排序信息选择对应的排序方式）
    void InsertionSort(Array &arr); // 直接插入排序
    void BubbleSort(Array &arr); // 冒泡排序
    void SelectSort(Array &arr); // 简单选择排序
    void QuickSort(Array &arr); // 快速排序
    void BinaryInsertionSort(Array &arr); // 折半插入排序
    void ShellSort(Array &arr); // 希尔排序
    void reSet(); // 重置
    int getTime(); // 获取比较次数
    int getTimeSwap(); // 获取交换次数
    void addTime(); // 增加比较次数
    void addTimeSwap(); // 增加交换次数
private:
    int part(Array& arr, int low, int height); // 快速排序用
    void quickSort(Array& arr, int low, int height); // 快速排序用
    int time; // 比较次数统计
    int time_swap; // 交换次数统计
};

#endif


