#ifndef __SORTINFO_H__
#define __SORTINFO_H__

#include <iostream>
#include <QPainter>

// 定义宏
#define INSERTION 0
#define BINARYINSERTION 1
#define SHELL 2
#define BUBBLE 3
#define QUICK 4
#define SELECT 5

#define CNST 6
#define N 7
#define N2 8
#define LOGN 9
#define NLOGN 10
#define N13 11

class SortInfo {
public:
    int type; // 排序类型
    int timeAVG; // 平均时间复杂度
    int timeBST; // 最佳时间复杂度
    int timeWST; // 最差时间复杂度
    int space; // 空间复杂度
    bool stable; // 稳定性
    SortInfo(int x); //构造函数
    void print(void); // 在console中打印排序信息（测试用）
    std::string name(); // 获取排序名称（测试用）
    void paint(QPainter &painter, int time, int time_swap); // 绘制排序信息
    void paintComplex(QPainter &painter, int x, int y, int c); // 绘制复杂度信息
    void change(int x); // 改变排序信息（按钮用）
private:
    void printComplex(int x); // 在console中打印复杂度信息（测试用）
};

#endif

