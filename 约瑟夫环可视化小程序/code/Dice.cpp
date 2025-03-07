#include "Dice.h"
#include <cstdlib>

Dice::Dice()
{
    // 构造函数
    num = 0;
}

void Dice::rollDice()
{
    // 投一次骰子
    // 采用以time为种子的随机数
    // 生成范围为1-6
    num = rand() % 6 + 1; // 骰子的取值范围为1-6
}

int Dice::getNum()
{
    // 获取骰子的值
    return num;
}

void Dice::paint(QPainter &painter)
{
    // 在右侧信息栏绘制骰子的文字信息
    painter.drawText(20,30,"当前骰子为：");
    painter.drawText(130, 30, QString::number(num));
}
