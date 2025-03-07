#include "Sorts.h"

Sorts::Sorts()
{
    time = 0;
    time_swap = 0;
}

void Sorts::sort(SortInfo info, Array arr)
{
    switch (info.type) {
        case INSERTION:
            InsertionSort(arr);
            break;
        case BINARYINSERTION:
            BinaryInsertionSort(arr);
            break;
        case SHELL:
            ShellSort(arr);
            break;
        case BUBBLE:
            BubbleSort(arr);
            break;
        case QUICK:
            QuickSort(arr);
            break;
        case SELECT:
            SelectSort(arr);
            break;
        default:
            QuickSort(arr);
            break;
    }
}

void Sorts::InsertionSort(Array& arr)
{
    int len = arr.getLen();
    for (int i = 1; i < len; i++) {
        int tmp = arr.getKth(i);
        for (int j = i - 1; j >= 0; j--) {
            int dataJ = arr.getKth(j);
            if (dataJ > tmp) {
                arr.changeKth(dataJ, j + 1);
                arr.changeKth(tmp, j);
                time++; // 交换次数加一
            }
            else
                break;
        }
    }
}

void Sorts::BubbleSort(Array& arr)
{
    int len = arr.getLen();
    for (int i = len - 1; i > 0; i--)
        for (int j = 0; j < i; j++)
            if (arr.getKth(j) > arr.getKth(j + 1)) {
                arr.swap(j, j + 1);
                time++; // 交换次数加一
            }
}

void Sorts::SelectSort(Array& arr)
{
    int len = arr.getLen();
    for (int i = 0; i < len; i++) {
        int index = i;
        for (int j = i + 1; j < len; j++)
            if (arr.getKth(index) > arr.getKth(j))
                index = j;
        arr.swap(i, index);
        time++;
    }
}

void Sorts::QuickSort(Array& arr)
{
    int len = arr.getLen();
    quickSort(arr, 0, len - 1);
}

void Sorts::quickSort(Array& arr, int low, int height)
{
    int mid;
    if (low < height) {
        mid = part(arr, low, height);
        quickSort(arr, low, mid - 1);
        quickSort(arr, mid + 1, height);
    }
}

int Sorts::part(Array& arr, int low, int height)
{
    int i = low, j = height, pivot = arr.getKth(low);
    while (i < j) {
        while (i < j && arr.getKth(j) > pivot)
            j--;
        if (i < j)
            arr.swap(i++, j);
        while (i < j && arr.getKth(i) <= pivot)
            i++;
        if (i < j)
            arr.swap(i, j--);
    }
    return i;
}

void Sorts::BinaryInsertionSort(Array& arr)
{
    int len = arr.getLen();
    for (int i = 1; i < len; i++) {
        int tmp = arr.getKth(i);
        int low = 0, height = i - 1;
        while (low <= height) {
            int mid = (low + height) / 2;
            if (arr.getKth(mid) < tmp)
                low = mid + 1;
            else
                height = mid - 1;
        }
        for (int j = i; j > low; j--){
            int tmp2 = arr.getKth(j - 1);
            arr.changeKth(tmp2, j);
        }
        arr.changeKth(tmp, low);
    }
}

void Sorts::ShellSort(Array& arr)
{
    int len = arr.getLen();
    int h = 1;
    while (h < len / 3)
        h = 3 * h + 1;
    while (h >= 1) {
        for (int i = h; i < len; i++)
            for (int j = i; j >= h && arr.getKth(j) < arr.getKth(j - h); j -= h){
                arr.swap(j, j - h);
                time++;
            }
        h = h / 3;
    }
}

void Sorts::reSet()
{
    time = 0;
    time_swap = 0;
}

int Sorts::getTime()
{
    return time;
}

int Sorts::getTimeSwap()
{
    return time_swap;
}

void Sorts::addTime()
{
    time++;
}

void Sorts::addTimeSwap()
{
    time_swap++;
}

