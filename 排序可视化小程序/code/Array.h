#ifndef __ARRAY_H__
#define __ARRAY_H__
#include <iostream>
#include <QPainter>

// 数组类
class Array {
private:
    int* data; // 数组元素
    int num; // 数组长度
    bool ready; // 数组是否设置好
public:
    Array(void); // 构造函数
    Array(int n); // 构造函数（测试用）
    ~Array(void); // 析构函数
    void randomInit(int n); // 随机初始化
    int getKth(int k); // 获取第k个元素
    int getLen(void); // 获取数组长度
    bool isReady(); // 判断数组是否设置好
    void changeKth(int x, int k); // 更改数组第k个元素为x
    void display(void); // 在console中打印数组（测试用）
    void swap(int i, int j); // 交换数组中i和j的值
    void changeNum(int n); // 改变数组长度（输入框用）
    void changeElem(const QString str); // 改变数组元素（输入框用）
    void paintText(QPainter &painter); // 绘制数组长度信息（gui用）
    void paintElemText(QPainter &painter); // 绘制数组元素信息（gui用）
    void reset(); // 重置数组
    void warning(); // 弹出警告框（数组未设置时）
    int getMax(); //  获取最大值
    void copy(Array &arr); // 复制数组
};

#endif
