#define _CRT_SECURE_NO_WARNINGS
#include "tools.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>

void InputData(int n, int* data)
{
    std::cout << "请手动输入数组(共" << n << "个)：" << std::endl;
    for (int i = 0; i < n; i++)
        std::cin >> data[i];
}

int getRand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}
