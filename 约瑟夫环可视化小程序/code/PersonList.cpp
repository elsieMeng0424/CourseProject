#include "PersonList.h"

PersonList::PersonList()
{
    // 构造函数
    num = 0;
    head = NULL;
}

PersonList::~PersonList()
{
    // 析构函数
    Person* p;
    while(head->next){
        p = head->next;
        delete head;
        head = p;
    }
    delete head;
}

Person *PersonList::getHead()
{
    // 返回头指针
    return head;
}

Person *PersonList::getKth(int k)
{
    // 获取第k个元素
    if(k < num && k >= 0){
        Person *p = head;
        for(int i = 0; i < k; i++)
            p = p->next;
        return p;
    }
    return NULL;
}

int PersonList::getNum()
{
    // 获取链表长度
    return num;
}

void PersonList::addPerson(Person *p)
{
    // 添加玩家
    if(!head){
        // 空链表
        head = p;
        num = 1;
    }
    else{
        // 非空链表
        Person* q = head;
        while(q->next){
            q = q->next;
        }
        q->next = p;
        num++;
    }
}

void PersonList::clear()
{
    // 清空链表
    if(num != 0){
        Person* p;
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


