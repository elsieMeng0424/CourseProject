#ifndef BARLIST_H
#define BARLIST_H

#include <QGraphicsRectItem>

// 定义结构体
struct barItem{
    QGraphicsRectItem *item;
    barItem *next;
    barItem(QGraphicsRectItem *i, barItem *n){
        item = i;
        next = n;
    }
};

// bar链表，代替QVector<QGraphicsRectItem>
class BarList{
private:
    barItem *head; // 头指针
    int num; // 链表长度
public:
    BarList(); // 构造函数
    ~BarList(); // 析构函数
    barItem *getHead(); // 获取头指针
    barItem *getKth(int k); // 获取第k个元素的指针
    int getNum(); // 获取链表长度
    void addBar(barItem *bar); // 添加元素
    void clear(); // 清空链表
    void setKth(QGraphicsRectItem *bar, int k); // 设置第k个元素的值
};

#endif // BARLIST_H
