/* 2251079 国06 隋建政 */
#include <iostream>
#include <iomanip>
#include "cmd_console_tools.h"
#include <conio.h>
#include <windows.h>
using namespace std;

extern int t, col[3], pla[3][10],delay;
void column()
{
    int x, y;
    int bg_color, fg_color;
    cct_setcursor(CURSOR_INVISIBLE);
    cct_showch(1, 15, 'x', 14, 14, 23);
    cct_showch(33, 15, 'x', 14, 14, 23);
    cct_showch(65, 15, 'x', 14, 14, 23);
    for (y = 14; y >= 3; y--) {
        for (x = 12; x <= 76; x += 32) {
            Sleep(50);
            cct_showch(x, y, 'x', 14, 14, 1);
        }
    }
    cct_setcolor(0, 7);
    cct_getcolor(bg_color, fg_color);
}
void plate(int n, char src)
{
    int x = 0, y = 14, i;
    int bg_color, fg_color;
    cct_setcursor(CURSOR_INVISIBLE);
    x = 12 + 32 * (src - 65);
    for (i = n; i > 0; i--) {
        Sleep(50);
        cct_showch(x - i, y, 'x', i, i, 2 * i + 1);
        y--;
    }
    cct_setcolor(0, 7);
    cct_getcolor(bg_color, fg_color);
}
void move(int n, char src, char dst, int num_src,int num_dst,int k,int delay)
{
    int x, y;
    int bg_color, fg_color;
    x = 12 + 32 * (src - 65) -n;
    if (delay)
        Sleep(1000 / delay);
    else
        Sleep(300);
    cct_setcursor(CURSOR_INVISIBLE);
    for (y = 14 - num_src; y >= 1; y--) {
        if (delay)
            Sleep(50 / delay);
        else
            Sleep(50);
        cct_showch(x, y, 'x', n, n, 2 * n + 1);
        cct_showch(x, y + 1, 'x', 0, 0, 2 * n + 1);
        cct_showch(x + n, y + 1, 'x', 14, 14, 1);
        if (y == 1)
            cct_showch(x + n, y + 1, 'x', 0, 0, 1);
    }
    y++;
    if (k) 
        if (num_src % 2 == 0)
            dst = 198 - dst - src;
    if (dst > src) {
        for (x++; x != 12 + 32 * (dst - 65)-n+1; x++) {
            if (delay) 
                Sleep(50 / delay);
            else
                Sleep(50);
            cct_showch(x, y, 'x', n, n, 2 * n + 1);
            cct_showch(x - 1, y, 'x', 0, 0, 1);
        }
        x--;
        y++;
    }
    else {
        for (x--; x != 12 + 32 * (dst - 65) - n-1; x--) {
            if (delay)
                Sleep(50 / delay);
            else
                Sleep(50);
            cct_showch(x, y, 'x', n, n, 2 * n + 1);
            cct_showch(x + 2 * n + 1, y, 'x', 0, 0, 1);
        }
        x++;
    }
    for (; y <= 14-num_dst; y++) {
        if (delay)
            Sleep(50 / delay);
        else
            Sleep(50);
        cct_showch(x, y, 'x', n, n, 2 * n + 1);
        if (y != 1) {
            cct_showch(x, y - 1, 'x', 0, 0, 2 * n + 1);
            cct_showch(x + n, y - 1, 'x', 14, 14, 1);
        }
        if (y <= 3&&y!=1)
            cct_showch(x + n, y - 1, 'x', 0, 0, 1);
    }
    cct_setcolor(0, 7);
    cct_getcolor(bg_color, fg_color);
}
void shuru_delay()
{
    while (1) {
        cout << "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)" << endl;
        cin >> delay;
        if (cin.good() && delay >= 0 && delay <= 5)
            break;
        else {
            cin.clear();
            cin.ignore(1024, '\n');
        }
    }
}

void shuru(int* n, char* src, char* tmp, char* dst,int option)
{
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 10; j++)
            pla[i][j] = 0;
    while (1) {
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> *n;
        while (1) {
            if (cin.good())
                break;
            else {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "请输入汉诺塔的层数(1-10)" << endl;
                cin >> *n;
            }
        }
        if (*n >= 1 && *n <= 10)
            break;
    }
    cin.clear();
    cin.ignore(1024, '\n');

    for (i = 0; i < *n; i++) {
        pla[0][i] = *n - i;
    }
    while (1) {
        cout << "请输入起始柱(A-C)" << endl;
        cin >> *src;

        while (1) {
            if (cin.good())
                break;
            else {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "请输入起始柱(A-C)" << endl;
                cin >> *src;
            }
        }
        if (*src == 97 || *src == 98 || *src == 99)
            *src -= 32;
        if (*src >= 65 && *src <= 67)
            break;
        cin.clear();
        cin.ignore(1024, '\n');
    }
    cin.clear();
    cin.ignore(10240, '\n');

    col[*src - 65] = 0;
    while (1) {
        cout << "请输入目标柱(A-C)" << endl;
        cin >> *dst;
        while (1) {
            if (cin.good())
                break;
            else {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "请输入目标柱(A-C)" << endl;
                cin >> *dst;
            }
        }
        if (*dst == 97 || *dst == 98 || *dst == 99)
            *dst -= 32;
        if (*dst >= 65 && *dst <= 67 && *dst != *src)
            break;
        if (*dst == *src)
            cout << "目标柱(" << *src << ")不能与起始柱(" << *src << ")相同" << endl;
        cin.clear();
        cin.ignore(1024, '\n');
    }
    cin.clear();
    cin.ignore(1024, '\n');
    col[*dst - 65] = 2;
    *tmp = 198 - *src - *dst;
    for (i = 0; i < 3; i++)
        if (i == *tmp - 65)
            col[i] = 1;
    if (option == 4||option==8)
        shuru_delay();
}
void shuchu3(int n, char src, char dst, int option)
{
    int i, x = 0,top1=0,top2=0;
    int num[3];
    for (i = 0; i < 3; i++)
        num[i] = 0;
    for (i = 0; i < 10; i++)
        if (pla[col[src-'A']][i] != 0)
            num[col[src-'A']]++;
    for (i = 0; i < 10; i++)
        if (pla[col[dst-'A']][i] != 0)
            num[col[dst-'A']]++;
    for (i = 0; i < 10; i++)
        if (pla[col[198-dst-src-'A']][i] != 0)
            num[col[198-dst-src-'A']]++;
    for (i = 0; i < 10; i++) {
        if (pla[col[src - 'A']][i] == 0)
            break;
        else
            top1 = pla[col[src - 'A']][i];
    }
    for (i = 0; i < 10; i++) {
        if (pla[col[dst - 'A']][i] == 0)
            break;
        else
            top2 = pla[col[dst - 'A']][i];
    }
    if (option == 9) {
        cct_gotoxy(0, 37);
        cout << "第" << setw(4) << t << " 步(" << top1 << "#): " << src << "-->" << dst;
    }
    if (option != 9 || (option == 9 && (num[col[src - 'A']] != 0 && (top1 < top2 || top2 == 0)))) {
        for (i = 0; i < 10; i++) {
            if (pla[col[src - 65]][i] == 0 && i != 0) {
                x = pla[col[src - 65]][i - 1];
                pla[col[src - 65]][i - 1] = 0;
                break;
            }
            else if (i == 9) {
                x = pla[col[src - 65]][i];
                pla[col[src - 65]][i] = 0;
                break;
            }
        }
        for (i = 0; i < 10; i++)
            if (pla[col[dst - 65]][i] == 0) {
                pla[col[dst - 65]][i] = x;
                break;
            }
    }
    cout << " A:";
    for (i = 0; i < 10; i++) {
        if (pla[col[0]][i] == 0)
            cout << "  ";
        else 
            cout << " " << pla[col[0]][i];
    }
    cout << " B:";
    for (i = 0; i < 10; i++) 
        if (pla[col[1]][i] == 0)
            cout << "  ";
        else {
            cout << " " << pla[col[1]][i];
        }
        cout << " C:";
    for (i = 0; i < 10; i++) 
        if (pla[col[2]][i] == 0)
            cout << "  ";
        else{
            cout << " " << pla[col[2]][i];
        }
    if (option == 8||option==9) {
        if (option == 9 && num[col[src - 'A']] == 0) {
            cout << endl;
            cout << endl;
            cout << endl;
            cout << "柱源为零";
            Sleep(500);
        }
        else if (option==9&&top1 > top2&&top2!=0) {
            cout << endl;
            cout << endl;
            cout << endl;
            cout << "大盘压小盘，非法移动";
            Sleep(500);
        }
        else {
            move(top1, src, dst, num[col[src - 'A']], num[col[dst - 'A']], 0, delay);
            if (option == 9)
                t++;
        }
    }
}
void shuchu4(int n,char src,char dst,int option)
{
    int ret,x=11,y=11,i;
    if (option == 8||option==9)
        y = 31;
    if (option != 9) {
        cct_gotoxy(0, 17);
        if (option == 8)
            cct_gotoxy(0, 37);
        cout << "第" << setw(4) << t << " 步(" << n << "#): " << src << "-->" << dst;
    }
    shuchu3(n,src, dst,option);
    cct_gotoxy(9, 12);
    if (option == 8||option==9)
        cct_gotoxy(9, 32);
    cout << "=========================";
    cct_gotoxy(x, y);
    for (i = 0; i < 10; i++) {
        if (pla[col[0]][i] == 0)
            cout << ' ';
        else {
            cout << pla[col[0]][i];
            y = y - 1;
            cct_gotoxy(x, y);
        }
    }
    x = 21;
    y = 11;
    if (option == 8||option==9)
        y=31;
    cct_gotoxy(x, y);
    for (i = 0; i < 10; i++) {
        if (pla[col[1]][i] == 0)
            cout << ' ';
        else {
            cout << pla[col[1]][i];
            y = y - 1;
            cct_gotoxy(x, y);
        }
    }
    x = 31;
    y = 11;
    if (option == 8||option==9)
        y = 31;
    cct_gotoxy(x, y);
    for (i = 0; i < 10; i++) {
        if (pla[col[2]][i] == 0)
            cout << ' ';
        else {
            cout << pla[col[2]][i];
            y = y - 1;
            cct_gotoxy(x, y);
        }
    }
    cct_gotoxy(11, 13);
    if (option == 8||option==9)
        cct_gotoxy(11, 33);
    cout << "A         B         C" << endl;
    if (option != 9) {
        if (!delay)
            while (1) {
                ret = _getch();
                if (ret == 13)
                    break;
            }
        else
            Sleep(1000 / delay);
    }
}

void print(int n, char src,char dst,char option)
{
    if (option == 1) {
        cout << n << "#" << " " << src << "---->" << dst << endl;
        t++;
    }
    if (option == 2||option==3) {
        cout << setiosflags(ios::right);
        cout << "第" << setw(4) << t << " 步( " << n << "#: " << src << "-->" << dst << ")";
        if (option == 3)
            shuchu3(n,src,dst,option);
        cout << endl;
        t++;
    }
    if (option == 4||option==8) {
        shuchu4(n,src,dst,option);
        t++;
    }
}

void hanoi(int n, char src, char tmp, char dst,int option)
{
    if (n == 1) 
        print(n, src, dst, option);
    else {
        hanoi(n - 1, src, dst, tmp,option);/*将上面（n-1）个移至中间柱*/
        print(n, src, dst, option);
        hanoi(n - 1, tmp, src, dst,option);/*将上面（n-1）个从中间柱移至目标柱*/
    }
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
}
void beginning()
{
    int i;
    cout << "初始: A:";
    for (i = 0; i < 10; i++) {
        if (pla[col[0]][i] == 0)
            cout << "  ";
        else
            cout << " " << pla[col[0]][i];
    }
    cout << " B:";
    for (i = 0; i < 10; i++) {
        if (pla[col[1]][i] == 0)
            cout << "  ";
        else
            cout << " " << pla[col[1]][i];
    }
    cout << " C:";
    for (i = 0; i < 10; i++) {
        if (pla[col[2]][i] == 0)
            cout << "  ";
        else
            cout << " " << pla[col[2]][i];
    }
}

void print4(char src,char tmp,char dst,int n,int option)
{
    int ret,i,x=11,y=11;
    if (option == 8 || option == 9)
        y += 20;
    cct_cls();
    if(option!=9)
        cout << "从" << src << "移动到" << dst << "，共" << n << "层，延时设置为" << delay << endl;
    else
        cout << "从" << src << "移动到" << dst << "，共" << n << "层" << endl;
    cct_gotoxy(0, 17);
    if (option == 8 || option == 9)
        cct_gotoxy(0, 37);
    beginning();
    cct_gotoxy(9, 12);
    if (option == 8 || option == 9)
        cct_gotoxy(9, 32);
    cout << "=========================";
    cct_gotoxy(x, y);
    for (i = 0; i < 10; i++) {
        if (pla[col[0]][i] == 0)
            break;
        else {
            cout << pla[col[0]][i];
            y = y - 1;
            cct_gotoxy(x, y);
        }
    }
    x = 21;
    cct_gotoxy(x, y);
    for (i = 0; i < 10; i++) {
        if (pla[col[1]][i] == 0)
            break;
        else {
            cout << pla[col[1]][i];
            y = y - 1;
            cct_gotoxy(x, y);
        }
    }
    x = 31;
    cct_gotoxy(x, y);
    for (i = 0; i < 10; i++) {
        if (pla[col[2]][i] == 0)
            break;
        else {
            cout << pla[col[2]][i];
            y = y - 1;
            cct_gotoxy(x, y);
        }
    }
    cct_gotoxy(11, 13);
    if (option == 8 || option == 9)
        cct_gotoxy(11, 33);
    cout << "A         B         C" << endl;
    if (option == 8||option==9) {
        column();
        plate(n, src);
    }
    if (option != 9) {
        if (!delay)
            while (1) {
                ret = _getch();
                if (ret == 13)
                    break;
            }
        else
            Sleep(1000 / delay);
    }
        hanoi(n, src, tmp, dst, option);
}
int mode9(int n,int option)
{
    char src_9, dst_9;
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    while (1) {
        cct_gotoxy(0, 39);
        cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：                          ";
        cout << endl;
        cout << "                                                ";
        cct_gotoxy(60, 39);
        cin >> src_9;
        if (src_9 == 'Q'||src_9=='q')
            return 1;
        else {
            cin >> dst_9;
            if (src_9 >= 'a' && src_9 <= 'c')
                src_9 -= 32;
            if (dst_9 >= 'a' && dst_9 <= 'c')
                dst_9 -= 32;
            if (src_9 >= 'A' && src_9 <= 'C' && dst_9 >= 'A' && dst_9 <= 'C' && dst_9 != src_9)
                break;
        }
    }
    cin.ignore();
    shuchu4(n, src_9, dst_9, option);
    return 0;
}