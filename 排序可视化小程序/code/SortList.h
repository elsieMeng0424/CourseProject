#ifndef SORTLIST_H
#define SORTLIST_H

struct recordItem{
    int value;
    recordItem *next;
    recordItem(int v, recordItem *n){
        value = v;
        next = n;
    }
};

class BarList{
private:
    recordItem *head;
    int num;
public:
    BarList();
    ~BarList();
    recordItem *getHead();
    recordItem *getKth(int k);
    int getNum();
    void addRecord(int v);
    void clear();
};

#endif // SORTLIST_H
