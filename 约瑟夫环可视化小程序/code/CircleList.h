#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include <QGraphicsEllipseItem>

// 定义结构体
struct circleItem{
    QGraphicsEllipseItem *item;
    circleItem *next;
    circleItem(QGraphicsEllipseItem *i, circleItem *n){
        item = i;
        next = n;
    }
};

// 圆圈链表类
// 代替QVector
class CircleList{
private:
    circleItem *head; // 头指针
    int num; // 链表长度
public:
    CircleList(); // 构造函数
    ~CircleList(); // 析构函数
    circleItem *getHead(); // 获取头指针
    circleItem *getKth(int k); // 获取第k个元素
    int getNum(); // 获取链表长度
    void addCircle(circleItem *c); // 添加圆圈元素
    void clear(); // 清空
};

#endif // CIRCLELIST_H
