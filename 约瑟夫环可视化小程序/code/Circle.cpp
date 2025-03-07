#include "Circle.h"

void Circle::getValue(Person*& p, std::string str, int n, Person* nextp)
{
    // 设置一个Person对象p的值
    p->name = str;
    p->No = n;
    p->next = nextp;
}

Circle::Circle()
{
    // 构造函数
    num = 0;
    head = NULL;
    tail = NULL;
}

Circle::~Circle()
{
    // 析构函数
    if (head) {
        Person* p = head->next;
        while (p != head) {
            head->next = p->next;
            delete p;
            p = head->next;
        }
        delete head;
    }
}

void Circle::AddPerson(std::string str, int n)
{
    // 添加一个成员
    // console测试用，输入为std::string
    Person* p = new Person(str,n,head);
    if (!head) {
        head = p;
        tail = p;
    }
    else {
        tail->next = p;
        tail = p;
    }
    num++;
}

void Circle::addPerson(const QString name)
{
    // 添加一个成员
    // Qt用，输入为QString，自动设置编号
    QString str;
    if(name.length() > 5)
        str = name.mid(0,5);
    else
        str = name;

    Person* p = new Person(str.toStdString(), num+1, head);
    if(!head){
        // 空circle
        head = p;
        tail = p;
    }
    else{
        // 非空，添加在末尾
        tail->next = p;
        tail = p;
    }
    num++;
}

void Circle::create(int n)
{
    // 创建长度为n的circle，console测试用
    std::cout << "请依次姓名:" << std::endl;
    int cnt = 1;
    for (int i = 0; i < n; i++) {
        std::string str;
        std::cin >> str;
        AddPerson(str, cnt); // 调用AddPerson函数
        cnt++;
    }
}

void Circle::display()
{
    // 展示所有成员信息
    // console测试用
//    std::cout << std::endl;
//    Person* p = head;
//    for (int i = 0; i < num; i++) {
//        std::cout << p->No << ' ' << p->name << std::endl;
//        p = p->next;
//    }
//    std::cout << std::endl;
}

void Circle::DeletePerson(Person* p)
{
    // 删去一个成员
    // 输入为Person对象p
    if (p == head) {
        // p为头指针
        tail->next = p->next;
        head = p->next;
        delete p;
    }
    else {
        // p不为头指针
        Person* q = p;
        while (q->next != p)
            q = q->next;
        q->next = p->next;
        if (p == tail)
            tail = q;
        delete p;
    }
    num--;
    if (num == 0) {
        // p为最后一个成员
        head = NULL;
        tail = NULL;
    }
}

Person* Circle::getKth(Person* start, int k)
{
    // 获取第k个成员
    // 从start开始计数
    // 输出为Person*
    Person* p = start;
    while (k > 1) {
        p = p->next;
        k--;
    }
    return p;
}

Person* Circle::getKthfromHead(int k)
{
    // 获取第k个成员
    // 从头指针开始计数
    // 输出为Person*
    Person* p = head;
    while (k > 1) {
        p = p->next;
        k--;
    }
    return p;
}

int Circle::getNum()
{
    // 获取成员数量
    return num;
}

Person* Circle::getHead()
{
    // 获取头指针
    return head;
}

Person* Circle::OneStep(Person* p, Dice* dice)
{
    // 进行一轮游戏
    // p为开始的成员指针（来自上一轮）
    dice->rollDice(); // 投一次骰子
    int k = dice->getNum();
    std::cout << "\n骰子的结果为：" << k << std::endl; // concole测试用
    Person* personOut = getKth(p, k); // 找出要被淘汰的成员
    Person* nextStart = NULL;
    // 若不存在剩余成员，则返回值为NULL
    if(num > 1)
        nextStart = personOut->next;
    DeletePerson(personOut); // 删除该成员
    display(); // console测试用
    return nextStart; // 返回下次开始时的成员指针
}

Person* Circle::play(Dice* dice)
{
    // 成员数量小于2，说明已经产生了胜者，剩下的唯一一个成员便是胜者
    if (num < 2)
        return head;
    // 进行一步游戏，获取下次开始的成员指针
    Person* nextStart = OneStep(head, dice);
    while (num > 1) {
        nextStart = OneStep(nextStart, dice);
    }
    std::cout << "最终胜者为:";
    printPerson(nextStart); // console测试用
    return nextStart; // 返回胜者指针
}

void Circle::paint(QPainter &painter)
{
    // 在gui页面中绘制circle的各项信息
    // 测试用
    painter.drawText(20, 20, "成员姓名");
    int startX = 100, startY = 20;
    Person* p = head;
    for(int i = 0; i < num; i++){
        painter.drawText(startX, startY, QString::fromStdString(p->name));
        p = p->next;
        startY += 30;
    }
}

void Circle::clear()
{
    // 清除所有成员
    if (num == 1){
        delete head;
    }
    else if (head) {
        Person* p = head->next;
        while (p != head) {
            head->next = p->next;
            delete p;
            p = head->next;
        }
        delete head;
    }
    head = NULL;
    tail = NULL;
    num = 0;
}

int Circle::getPersonNum(Person *p)
{
    // 获取p指针的位置（0-num-1）
    Person* q = head;
    int res = 0;
    for(int i = 0; i < num; i++){
        if(q == p)
            break;
        else{
            q = q->next;
            res++;
        }
    }
    return res;
}

void Circle::printPerson(Person* p)
{
    // console测试用
    std::cout << p->No << ' ' << p->name << std::endl;
}
