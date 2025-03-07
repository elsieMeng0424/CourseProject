#include "Array.h"
#include "tools.h"
#include <iostream>
#include <QMessageBox>
#include <QPushButton>

Array::Array()
{
    // 初始化
    num = 0;
    data = NULL;
    ready = false;
}

Array::Array(int n)
{
    // 测试用（从键盘输入）
    num = n;
    data = new int[n];
    InputData(num, data);
    ready = true;
}

Array::~Array()
{
    // 析构
    delete data;
}

void Array::randomInit(int n)
{
    // 若数组还未设定，弹出警告框
    if(n == 0){
        warning();
        return;
    }

    // 随机生成n个元素（0-100）
    num = n;
    data = new int[num];
    for (int i = 0; i < num; i++)
        data[i] = getRand(0, 100);
    ready = true;
}

int Array::getKth(int k)
{
    // 错误报警
    if (k >= num) {
        std::cout << "超过数组额度" << std::endl;
        return 0;
    }
    return data[k]; // 返回第k个元素
}

int Array::getLen()
{
    return num; // 返回数组长度
}

bool Array::isReady()
{
    return ready; // 返回数组是否设定好
}

void Array::changeKth(int x, int k)
{
    // 错误报警
    if (k >= num) {
        std::cout << "超过数组额度" << std::endl;
        return;
    }
    data[k] = x; // 将第k个元素更换为x
}

void Array::display()
{
    // 在console中打印，测试用
    for (int i = 0; i < num; i++)
        std::cout << data[i] << ' ';
    std::cout << std::endl;
}

void Array::swap(int i, int j)
{
    // 交换i和j的值
    int tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
}

void Array::changeNum(int n)
{
    // 改变数组长度
    num = n;
    // 将元素初始值全部设置为0
    data = new int[num];
    for(int i = 0; i < n; i++)
        data[i] = 0;
    // 由于还未填值，因此此时的数组也算作没有设定好
    ready = false;
}

void Array::changeElem(const QString str)
{
    // 弹出警告框
    if(num == 0){
        warning();
        return;
    }
    reset(); // 先将数组重置
    int i = 0;
    QString strElem = "";
    for(int j = 0; j < str.length(); j++){
        if(str[j] < '0' || str[j] > '9'){ // 设计了一定的错误处理功能，不光空格，所有非数字符号都可以作为分隔符
            if(strElem != ""){
                data[i] = strElem.toInt();
                i++;
                strElem = "";
            }
        }
        else
            strElem = strElem + str[j];
    }
    data[i] = strElem.toInt();
    // 注意此时若是填入的数量小于数组长度，多余的元素均为0
    ready = true; // 数组已设定好
}

void Array::paintText(QPainter &painter)
{
    const QString strNum = QString::number(num);
    painter.drawText(10,20,"数组长度：");
    painter.drawText(100,20,strNum);
}

void Array::paintElemText(QPainter &painter)
{
    // 绘制数组元素
    // 按数组元素个数均分
    int start = 0, end = 1270;
    int gap = (end - start) / num;
    start = gap / 2;
    for(int i = 0; i < num; i++){
        const QString strElem = QString::number(data[i]);
        painter.drawText(start,30,strElem);
        start += gap;
    }
}

void Array::reset()
{
    // 重置数组，长度不变，元素全部设置为0
    for(int i = 0; i < num; i++)
        data[i] = 0;
}

void Array::warning()
{
    // 弹出警告框
    QMessageBox box;
    box.setWindowTitle("警告");
    box.setIcon(QMessageBox::Warning);
    box.setText("尚未设置数组长度，请设置数组长度");
    QPushButton *yesBtn = box.addButton("是(&Y)", QMessageBox::YesRole);
    box.exec();
    if(box.clickedButton() == yesBtn)
        return;
}

int Array::getMax()
{
    // 获取最大值
    int maxValue = -1;
    for(int i = 0; i < num; i++){
        if(data[i] > maxValue)
            maxValue = data[i];
    }
    return maxValue;
}

void Array::copy(Array &arr)
{
    // 复制arr
    num = arr.getLen();
    data = new int[num];
    for(int i = 0; i < num; i++){
        data[i] = arr.getKth(i);
    }
}
