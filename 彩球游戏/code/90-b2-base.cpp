/* 2251079 国06 隋建政 */
#include <iostream>
#include <windows.h>
using namespace std;
#include "90-b2.h"

void input_five_balls(int ball[9][9], int row, int column)
{
	int n=0,i,j;
	srand((unsigned int)(time(0)));
	while (n < 5) {
		i = rand() % row;
		j = rand() % column;
		if (ball[i][j] == 0) {
			ball[i][j] = rand() % 7 + 1;
			n++;
		}
	}
}

void input_60_percent(int ball[9][9], int row, int column)
{
	int sum = int(row * column * 0.6),n=0,i,j;
	srand((unsigned int)(time(0)));
	while (n < sum) {
		i = rand() % row;
		j = rand() % column;
		if (ball[i][j] == 0) {
			ball[i][j] = rand() % 7 + 1;
			n++;
		}
	}
}

void input_next(int ball[9][9], int row, int column, int next1, int next2, int next3, int n)
{
	int i, j;
	srand((unsigned int)(time(0)));
	while (1) {
		i = rand() % row;
		j = rand() % column;
		if (ball[i][j] == 0) {
			ball[i][j] = next1;
			break;
		}
	}
	if (n >= 2) 
		while (1) {
			i = rand() % row;
			j = rand() % column;
			if (ball[i][j] == 0) {
				ball[i][j] = next2;
				break;
			}
		}
	if (n >= 3) 
		while (1) {
			i = rand() % row;
			j = rand() % column;
			if (ball[i][j] == 0) {
				ball[i][j] = next3;
				break;
			}
		}
}

void prediction(int* p_next1, int* p_next2, int* p_next3,int option)
{
	srand((unsigned int)(time(0)));
	*p_next1 = rand() % 7 + 1;
	*p_next2 = rand() % 7 + 1;
	*p_next3 = rand() % 7 + 1;
	if(option!=7)
	    cout << "下3个彩球的颜色分别是:" << *p_next1 << ' ' << *p_next2 << ' ' << *p_next3 << endl;
}

void output2(int ball[9][9], int row, int column, int* p_num_src, int* p_num_dst, char* p_src, char* p_dst)
{
	int x, y;
	while (1) {
		cout << "请以字母+数字形式[例:c2]输入要移动球的矩阵坐标:";
		cct_getxy(x, y);
		while (1) {
			cct_gotoxy(x, y);
			cin >> *p_src >> *p_num_src;
			if (*p_src >= 'a')
				*p_src -= 32;
			if (*p_src >= 'A' && *p_src <= 64 + row && *p_num_src >= 1 && *p_num_src <= column)
				break;
			else {
				cct_gotoxy(x, y);
				cout << "                                                           " << endl;
				cout << "输入错误，请重新输入";
				cin.clear();
				cin.ignore(1024, '\n');
			}
		}
		if (ball[*p_src - 65][*p_num_src - 1] == 0) {
			cout << "起始位置为空，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	cin.clear();
	cin.ignore(1024, '\n');
	cout << "输入为" << *p_src << "行" << *p_num_src << "列" << endl;
	while (1) {
		cout << "请以字母+数字形式[例:c2]输入要移动球的目的坐标:";
		cct_getxy(x, y);
		while (1) {
			cct_gotoxy(x, y);
			cin >> *p_dst >> *p_num_dst;
			if (*p_dst >= 'a')
				*p_dst -= 32;
			if (*p_dst >= 'A' && *p_dst <= 64 + row && *p_num_dst >= 1 && *p_num_dst <= column)
				break;
			else {
				cct_gotoxy(x, y);
				cout << "                                                           " << endl;
				cout << "输入错误，请重新输入";
				cin.clear();
				cin.ignore(1024, '\n');
			}
		}
		if (ball[*p_dst - 65][*p_num_dst - 1] != 0) {
			cout << "目标位置非空，请重新输入" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	cin.clear();
	cin.ignore(1024, '\n');
	cout << "输入为" << *p_dst << "行" << *p_num_dst << "列" << endl;
}

void del_score(int ball[9][9], int del[100][2],int elm[8])
{
	int i;
	for (i = 0; i < 100 && del[i][0] != -1; i++) {
		elm[ball[del[i][0]][del[i][1]]]++;
		ball[del[i][0]][del[i][1]] = 0;
	}
}