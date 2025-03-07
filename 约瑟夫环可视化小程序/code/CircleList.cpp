#include <CircleList.h>


CircleList::CircleList()
{
    // 构造函数
    head = NULL;
    num = 0;
}

CircleList::~CircleList()
{
    // 析构函数
    circleItem* p;
    while(head->next){
        p = head->next;
        delete head;
        head = p;
    }
    delete head;
}

circleItem *CircleList::getHead()
{
    // 获取头指针
    return head;
}

circleItem *CircleList::getKth(int k)
{
    // 获取第k个元素的指针
    if(k < num && k >= 0){
        circleItem *p = head;
        for(int i = 0; i < k; i++)
            p = p->next;
        return p;
    }
    return NULL;
}

int CircleList::getNum()
{
    // 获取链表数量
    return num;
}

void CircleList::addCircle(circleItem *c)
{
    // 添加对象
    if(!head){
        // 空链表
        head = c;
        num = 1;
    }
    else{
        circleItem* q = head;
        while(q->next){
            q = q->next;
        }
        q->next = c;
        num++;
    }
}

void CircleList::clear()
{
    // 清空链表
    if(head){
        circleItem* p;
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




