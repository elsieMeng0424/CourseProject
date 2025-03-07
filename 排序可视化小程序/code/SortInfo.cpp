#include "SortInfo.h"
#include <iostream>

SortInfo::SortInfo(int x)
{
    change(x);
}

void SortInfo::print()
{
    // console测试用
    std::cout << std::endl;
    switch (type) {
        case INSERTION:
            std::cout << "排序类型：直接插入排序" << std::endl;
            break;
        case BINARYINSERTION:
            std::cout << "排序类型：折半插入排序" << std::endl;
            break;
        case SHELL:
            std::cout << "排序类型：希尔排序" << std::endl;
            break;
        case BUBBLE:
            std::cout << "排序类型：冒泡排序" << std::endl;
            break;
        case QUICK:
            std::cout << "排序类型：快速排序" << std::endl;
            break;
        case SELECT:
            std::cout << "排序类型：简单选择排序" << std::endl;
            break;
        default:
            std::cout << "排序类型：错误类型" << std::endl;
            break;
    }
    std::cout << "平均时间复杂度：";
    printComplex(timeAVG);
    std::cout << "最佳时间复杂度：";
    printComplex(timeBST);
    std::cout << "最差时间复杂度：";
    printComplex(timeWST);
    std::cout << "空间复杂度：";
    printComplex(space);
    std::cout << "稳定性：" << (stable ? "稳定" : "不稳定") << std::endl;
    std::cout << std::endl;
}

std::string SortInfo::name()
{
    switch(type){
    case INSERTION: return "直接插入排序";
    case BINARYINSERTION: return "折半插入排序";
    case SHELL: return "希尔排序";
    case BUBBLE: return "冒泡排序";
    case QUICK: return "快速排序";
    case SELECT: return "简单选择排序";
    default: return "错误类型";
    }
}

void SortInfo::paint(QPainter &painter, int time, int time_swap)
{
    // 绘制排序信息（gui）
    painter.drawText(20,50,"排序类型：");
    switch (type) {
        case INSERTION:
            painter.drawText(150,50,"直接插入排序");
            break;
        case BINARYINSERTION:
            painter.drawText(150,50,"折半插入排序");
            break;
        case SHELL:
            painter.drawText(150,50,"希尔排序");
            break;
        case BUBBLE:
            painter.drawText(150,50,"冒泡排序");
            break;
        case QUICK:
            painter.drawText(150,50,"快速排序");
            break;
        case SELECT:
            painter.drawText(150,50,"简单选择排序");
            break;
        default:
            painter.drawText(150,50,"排序类型：错误类型");
            break;
    }
    painter.drawText(350,50,"比较次数：");
    const QString strTime = QString::number(time);
    painter.drawText(450,50,strTime);

    painter.drawText(600, 50, "交换次数：");
    const QString strTimeSwap = QString::number(time_swap);
    painter.drawText(700, 50, strTimeSwap);

    painter.drawText(20,110,"平均时间复杂度：");
    paintComplex(painter, 190, 110, timeAVG);
    painter.drawText(300,110,"最佳时间复杂度：");
    paintComplex(painter, 470, 110, timeBST);
    painter.drawText(580,110,"最差时间复杂度：");
    paintComplex(painter, 750, 110, timeWST);
    painter.drawText(860,110,"空间复杂度：");
    paintComplex(painter, 1000, 110, space);
    painter.drawText(1100,110,"稳定性：");
    if(stable)
        painter.drawText(1180,110,"稳定");
    else
        painter.drawText(1180,110,"不稳定");
}

void SortInfo::paintComplex(QPainter &painter, int x, int y, int c)
{
    // 绘制复杂度（gui中）
    switch (c) {
        case N:
            painter.drawText(x, y, "O(N)");
            break;
        case N2:
            painter.drawText(x, y, "O(N^2)");
            break;
        case N13:
            painter.drawText(x, y, "O(N^1.3)");
            break;
        case CNST:
            painter.drawText(x, y, "O(1)");
            break;
        case LOGN:
            painter.drawText(x, y, "O(logN)");
            break;
        case NLOGN:
            painter.drawText(x, y, "O(NlogN)");
            break;
        default:
            painter.drawText(x, y, "错误类型");
            break;
    }
}

void SortInfo::change(int x)
{
    // 更改排序类型
    type = x;
    if (type == INSERTION) {
        timeAVG = N2;
        timeBST = N;
        timeWST = N2;
        space = CNST;
        stable = true;
    }
    else if (type == BINARYINSERTION) {
        timeAVG = N2;
        timeBST = N;
        timeWST = N2;
        space = CNST;
        stable = true;
    }
    else if (type == SHELL) {
        timeAVG = N13;
        timeBST = N;
        timeWST = N2;
        space = CNST;
        stable = false;
    }
    else if (type == BUBBLE) {
        timeAVG = N2;
        timeBST = N;
        timeWST = N2;
        space = CNST;
        stable = true;
    }
    else if (type == QUICK) {
        timeAVG = NLOGN;
        timeBST = NLOGN;
        timeWST = N2;
        space = LOGN;
        stable = false;
    }
    else if (type == SELECT) {
        timeAVG = N2;
        timeBST = N2;
        timeWST = N2;
        space = CNST;
        stable = false;
    }
    else {
        timeAVG = -1;
        timeBST = -1;
        timeWST = -1;
        space = -1;
        stable = false;
    }
}

void SortInfo::printComplex(int x)
{
    // 打印复杂度
    // console测试用
    switch (x) {
        case N:
            std::cout << "O(n)" << std::endl;
            break;
        case N2:
            std::cout << "O(n^2)" << std::endl;
            break;
        case N13:
            std::cout << "O(n^1.3)" << std::endl;
            break;
        case CNST:
            std::cout << "O(1)" << std::endl;
            break;
        case LOGN:
            std::cout << "O(logn)" << std::endl;
            break;
        case NLOGN:
            std::cout << "O(nlogn)" << std::endl;
            break;
        default:
            std::cout << "错误类型" << std::endl;
            break;
    }
}
