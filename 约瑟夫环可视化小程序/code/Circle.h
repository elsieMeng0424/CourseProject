#ifndef CIRCLE_H
#define CIRCLE_H

#include "Dice.h"
#include <iostream>
#include <QString>

// Person结构体
struct Person {
    std::string name; // 成员姓名
    int No; // 成员编号
    Person* next; // 下一位成员
    Person(std::string n, int no, Person* nx){
        name = n;
        No = no;
        next = nx;
    }
};

// Circle类
// 表示游戏成员组成的圆圈
// 用循环链表数据结构进行表示
class Circle {
public:
    Circle(); // 构造函数
    ~Circle(); // 析构函数
    int getNum(); // 获取成员数量
    Person* getHead(); // 获取头指针
    Person* getKth(Person* start, int k); // 获取第k个成员的指针（从start开始）
    Person* getKthfromHead(int k); // 获取第k个成员的指针（从head开始）
    void AddPerson(std::string name, int No); // 添加成员（姓名，编号）
    void addPerson(const QString name); // 添加成员（姓名，自动设置编号）
    void DeletePerson(Person* p); // 删除成员
    void create(int n); // 创建长度为n的circle（测试用）
    void display(void); // 打印circle信息（console测试用）
    void printPerson(Person* p); // 打印成员信息（console测试用）
    Person* OneStep(Person* start, Dice* dice); // 进行一轮游戏（投骰子，淘汰一人）
    Person* play(Dice* dice); // 进行整个游戏（打印最后的赢家）
    void paint(QPainter &painter); // 绘制circle信息（测试用Qt）
    void clear(); // 清除所有成员
    int getPersonNum(Person* p);
private:
    Person* head; // 头指针
    Person* tail; // 尾指针
    int num; // 数量
    void getValue(Person*& p, std::string str, int n, Person* nextp); // 设置某一成员的值
};

#endif // CIRCLE_H
