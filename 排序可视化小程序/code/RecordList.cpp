#include "RecordList.h"
#include <iostream>

recordList::recordList()
{
    // 构造函数
    head = NULL;
    num = 0;
}

recordList::~recordList()
{
    // 析构函数
    recordItem* p;
    while(head->next){
        p = head->next;
        delete head;
        head = p;
    }
    delete head;
}

recordItem *recordList::getHead()
{
    // 返回头指针
    return head;
}

int recordList::getKth(int k)
{
    // 获取第k个元素
    if(k < num && k >= 0){
        recordItem *p = head;
        for(int i = 0; i < k; i++)
            p = p->next;
        return p->value;
    }
    return -1;
}

int recordList::getNum()
{
    // 获取长度
    return num;
}

void recordList::addRecord(int v)
{
    // 添加记录
    recordItem *ri = new recordItem(v, NULL);
    if(!head){
        head = ri;
        num = 1;
    }
    else{
        recordItem* q = head;
        while(q->next){
            q = q->next;
        }
        q->next = ri;
        num++;
    }
}

void recordList::clear()
{
    // 清空链表
    if(head){
        recordItem* p;
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




