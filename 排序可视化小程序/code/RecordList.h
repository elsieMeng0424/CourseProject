#ifndef RECORDLIST_H
#define RECORDLIST_H

// 定义结构体
struct recordItem{
    int value;
    recordItem *next;
    recordItem(int v, recordItem *n){
        value = v;
        next = n;
    }
};

// 记录链表，用于记录快速排序的步骤
class recordList{
private:
    recordItem *head; // 头指针
    int num; // 链表长度
public:
    recordList(); // 构造函数
    ~recordList(); // 析构函数
    recordItem *getHead(); // 获取头指针
    int getKth(int k); // 获取第k个元素
    int getNum(); // 获取链表长度
    void addRecord(int v); // 添加记录元素（两位合成一个记录）
    void clear(); // 清空
};

#endif // RECORDLIST_H
