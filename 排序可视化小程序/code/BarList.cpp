#include "BarList.h"


BarList::BarList()
{
    // 构造函数
    head = NULL;
    num = 0;
}

BarList::~BarList()
{
    // 析构函数
    barItem* p;
    while(head->next){
        p = head->next;
        delete head;
        head = p;
    }
    delete head;
}

barItem *BarList::getHead()
{
    // 返回头指针
    return head;
}

barItem *BarList::getKth(int k)
{
    // 获取第k个元素的值
    if(k < num && k >= 0){
        barItem *p = head;
        for(int i = 0; i < k; i++)
            p = p->next;
        return p;
    }
    return NULL;
}

int BarList::getNum()
{
    // 获取链表程度
    return num;
}

void BarList::addBar(barItem *bar)
{
    // 添加长方形对象
    if(!head){
        // 如果是空链表
        head = bar;
        num = 1;
    }
    else{
        // 如果不是空链表
        barItem* q = head;
        while(q->next){
            q = q->next;
        } // 找到尾指针
        q->next = bar;
        num++; // 长度加一
    }
}

void BarList::clear()
{
    // 清空链表
    if(head){
        // 如果链表非空
        barItem* p;
        while(head->next){
            p = head->next;
            delete head;
            head = p;
        }
        delete head;
        head = NULL;
        num = 0;
    }
}

void BarList::setKth(QGraphicsRectItem *bar, int k)
{
    // 设置第k个元素的值
    barItem *p = head;
    for(int i = 0; i < k ;i++){
        p = p->next;
    }
    p->item = bar;
}






