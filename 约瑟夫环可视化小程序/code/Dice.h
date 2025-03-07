#ifndef DICE_H
#define DICE_H

#include <QPainter>

// Dice类
// 完成骰子的各项操作
class Dice{
private:
    int num; // 骰子的值
public:
    Dice(); // 构造函数
    void rollDice(); // 投骰子，生成1-6的值
    int getNum(); // 获取骰子的值
    void paint(QPainter &painter); // 绘制骰子信息
};

#endif // DICE_H
