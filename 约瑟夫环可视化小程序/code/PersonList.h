#ifndef PERSONLIST_H
#define PERSONLIST_H

#include "Circle.h"

class PersonList{
private:
    Person* head; // 头指针
    int num; // 链表数量
public:
    PersonList(); // 构造函数
    ~PersonList(); // 析构函数
    Person *getHead(); // 获取头指针
    Person *getKth(int k); // 获取第k个指针
    int getNum(); // 获取数量
    void addPerson(Person *p); // 添加玩家
    void clear(); // 清空链表
};

#endif // PERSONLIST_H
