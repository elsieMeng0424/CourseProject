#pragma once
#include <iostream>
using namespace std;

class Array
{
public:
    template <typename... Args>
    Array(Args... args){
        auto num = int(sizeof...(args));
        int list[3] = { args... };
        int count = 1;
        for (int i = 0; i < num; i++) {
            count *= int(list[i]);
            shape[i] = int(list[i]);
        }
        data = new int[count * sizeof(int)];
        axisNum = num;
        nowAxis = 0;
        index = 0;
    }

    Array(Array& a)
    {
        axisNum = a.axisNum;
        index = 0;
        nowAxis = 0;
        int count = 1;
        for (int i = 0; i < axisNum; i++) {
            shape[i] = a.shape[i];
            count *= shape[i];
        }
        data = new int[count * sizeof(int)];
    }

    template <typename... Args>
    Array& at(Args... args)
    {
        // 获取参数包大小并转换为size_t数组
        auto num = sizeof...(args);
        size_t list[3] = { args... };

        index = 0;
        for (int i = 0; i < num; i++)
        {
            int size = 1;
            for (int j = i + 1; j < num; j++)
                size *= shape[j];
            index += size * int(list[i]);
        }
        return *this;
    }

    template <typename... Args>
    void reshape(Args... args)
    {
        // 获取参数包大小并转换为size_t数组
        auto num = sizeof...(args);
        size_t list[] = { args... };

        for (int i = 0; i < axisNum; i++)
            shape[i] = 0;
        axisNum = num;
        for (int i = 0; i < axisNum; i++)
            shape[i] = int(list[i]);

    }

    int* get_content() { return data; }

    void set(int value) { data[index] = value; }

    Array& operator[](int in)
    {
        // 在这里修改子矩阵的nowAxis的值以及其他有必要的值，以返回一个子矩阵
        int size = 1;
        if (nowAxis == 0)
            index = 0;
        for (int i = nowAxis + 1; i < axisNum; i++) {
            size *= shape[i];
        }
        index += in * size;
        nowAxis++;
        nowAxis = nowAxis % axisNum;
        return *this;
    }

    Array& operator=(int data)
    {
        this->data[index] = data;
        return *this;
    }

    Array& operator=(Array& a)
    {
        int len = 1;
        for (int i = 0; i < a.axisNum; i++)
            len *= a.shape[i];
        for (int i = 0; i < len; i++)
            data[i] = a.data[i];
        return *this;
    }

    Array& operator+(Array& b)
    {
        Array& sum = b;
        int len = 1;
        for (int i = 0; i < axisNum; i++)
            len *= shape[i];
        for (int i = 0; i < len; i++) {
            sum.data[i] = data[i] + b.data[i];
        }
        return sum;
    }

    Array& operator-(Array& b)
    {
        Array& dif = b;
        int len = 1;
        for (int i = 0; i < axisNum; i++)
            len *= shape[i];
        for (int i = 0; i < len; i++) {
            dif.data[i] = data[i] - b.data[i];
        }
        return dif;
    }

    Array& operator*(Array& b)
    {
        Array& pro = b;
        int len = 1;
        for (int i = 0; i < axisNum; i++)
            len *= shape[i];
        for (int i = 0; i < len; i++) {
            pro.data[i] = data[i] * b.data[i];
        }
        return pro;
    }

    operator int() { return data[index]; }
    friend ostream& operator<<(ostream&, Array&);

    void set_shape(int x, int y)
    {
        shape[0] = x;
        shape[1] = y;
        shape[2] = 4;
        data = new int[x * y * 4 * sizeof(int)];
        axisNum = 3;
        nowAxis = 0;
        index = 0;
    }

    ~Array()
    {
        delete[]data;
    }
    int* data;
    int index;
    int shape[16];
    int axisNum;
    int nowAxis;
};

ostream& operator<<(ostream& out, Array& a)
{
    out << a.data[a.index];
    return out;
}

Array& operator+(Array& a, int add)
{
    Array& sum = a;
    int len = 1;
    for (int i = 0; i < a.axisNum; i++)
        len *= a.shape[i];
    for (int i = 0; i < len; i++) {
        sum.data[i] = a.data[i] + add;
    }
    return sum;
}

Array& operator-(Array& a, int drp)
{
    Array& dif = a;
    int len = 1;
    for (int i = 0; i < a.axisNum; i++)
        len *= a.shape[i];
    for (int i = 0; i < len; i++) {
        dif.data[i] = a.data[i] - drp;
    }
    return dif;
}

Array& operator*(Array& a, int k)
{
    Array& pro = a;
    int len = 1;
    for (int i = 0; i < a.axisNum; i++)
        len *= a.shape[i];
    for (int i = 0; i < len; i++) {
        pro.data[i] = a.data[i] * k;
    }
    return pro;
}