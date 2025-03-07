/* 2251079 国06 隋建政 */
#include <iostream>
using namespace std;
#include "90-b2.h"

void input(int *p_row,int *p_column)
{
	while (1) {
		cout << "请输入行数" << endl;
		cin >> *p_row;
		if (cin.good() && *p_row >= 7 && *p_row <= 9)
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}
	cin.clear();
	cin.ignore(1024, '\n');

	while (1) {
		cout << "请输入列数" << endl;
		cin >> *p_column;
		if (cin.good() && *p_column >= 7 && *p_column <= 9)
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}
	cin.clear();
	cin.ignore(1024, '\n');
}

void End()
{
	int x, y;
	char a, b, c;
	cout << "本小题结束，请输入End继续...";
	cct_getxy(x, y);
	while (1) {
		cct_gotoxy(x, y);
		cin >> a >> b >> c;
		if ((a == 'E'||a=='e') && (b == 'n'||b=='N') && (c == 'd'||c=='D'))
			break;
		else {
			cout << "输入错误，请重新输入";
			cct_gotoxy(x, y);
			cout << "       ";
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
}

int search_way(int ball[9][9], int x_src, int x_dst, int y_src, int y_dst,int row,int column,int way[100][2],int *p_num)
{
	if (x_src >= 0 && x_src < column && y_src >= 0 && y_src < row)
	{
		if (x_src == x_dst && y_src == y_dst) {
			way[*p_num][0] = y_dst;
			way[*p_num][1] = x_dst;
			(* p_num)++;
			return 1;
		}
		else
			ball[y_src][x_src] = -1;

		if (ball[y_src][x_src + 1] == 0) {
			search_way(ball, x_src + 1, x_dst, y_src, y_dst, row, column, way, p_num);
			if (*p_num) {
				way[*p_num][0] = y_src;
				way[*p_num][1] = x_src;
				(* p_num)++;
				return 1;
			}
		}
		if (ball[y_src][x_src - 1] == 0) {
			search_way(ball, x_src - 1, x_dst, y_src, y_dst, row, column, way, p_num);
			if (*p_num) {
				way[*p_num][0] = y_src;
				way[*p_num][1] = x_src;
				(* p_num)++;
				return 1;
			}
		}
		if (ball[y_src + 1][x_src] == 0) {
			search_way(ball, x_src, x_dst, y_src + 1, y_dst, row, column, way, p_num);
			if (*p_num) {
				way[*p_num][0] = y_src;
				way[*p_num][1] = x_src;
				(* p_num)++;
				return 1;
			}
		}
		if (ball[y_src - 1][x_src] == 0) {
			search_way(ball, x_src , x_dst, y_src - 1, y_dst, row, column, way, p_num);
			if (*p_num) {
				way[*p_num][0] = y_src;
				way[*p_num][1] = x_src;
				(* p_num)++;
				return 1;
			}
		}
		return 0;
	}
	else
		return 0;
}

void check_score(int ball[9][9],int row,int column,int *p_score_once,int del[100][2])
{
	int i, j, n, count = 1, repeat[4],num=0;
	for (i = 0; i < 4; i++)
		repeat[i] = 0;
	for(i=0;i<row;i++)
		for (j = 0; j < column; j++) {
			if (j + 4 < column) {
				count = 1;
				for ( n = 1; n + j < column; n++) {
					if (ball[i][n + j] != ball[i][n + j - 1])
						break;
					else if(ball[i][n+j]!=0)
						count++;
				}
				if (count > 4) {
					for (n = 0; n < count; n++) {
						del[num][0] = i;
						del[num][1] = j + n;
						num++;
					}
					(*p_score_once) += (count - 1) * (count - 2);
					if (count > 5)
						repeat[count - 6]++;
				}
			}
			if (i + 4 < row) {
				count = 1;
				for ( n = 1; n + i < row; n++) {
					if (ball[i+n][j] != ball[i+n-1][j])
						break;
					else if(ball[i+n][j]!=0)
						count++;
				}
				if (count > 4) {
					for (n = 0; n < count; n++) {
						del[num][0] = i+n;
						del[num][1] = j;
						num++;
					}
					(*p_score_once) += (count - 1) * (count - 2);
					if (count > 5)
						repeat[count - 6]++;
				}
			}
			if (i + 4 < row && j + 4 < column) {
				count = 1;
				for (n = 1; n + i < row && n + j < column; n++) {
					if (ball[i + n][j + n] != ball[i + n - 1][j + n - 1])
						break;
					else if (ball[i + n][j + n] != 0)
						count++;
				}
				if (count > 4) {
					for (n = 0; n < count; n++) {
						del[num][0] = i + n;
						del[num][1] = j + n;
						num++;
					}
					(*p_score_once) += (count - 1) * (count - 2);
					if (count > 5)
						repeat[count - 6]++;
				}
			}
			if (i >= 4 && j + 4 < column) {
				count = 1;
				for (n = 1;i-n>=0 &&n + j < column; n++) {
					if (ball[i - n][j + n] != ball[i - n + 1][j + n - 1])
						break;
					else if (ball[i - n][j + n] != 0)
						count++;
				}
				if (count > 4) {
					for (n = 0; n < count; n++) {
						del[num][0] = i - n;
						del[num][1] = j + n;
						num++;
					}
					(*p_score_once) += (count - 1) * (count - 2);
					if (count > 5)
						repeat[count - 6]++;
				}
			}
		}
	*p_score_once -= (repeat[0] * 12 + repeat[1] * 20 + repeat[2] * 30 + repeat[3] * 42);
}

int check_of_end(int ball[9][9],int row, int column)
{
	int i, j,count=0;
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
			if (ball[i][j] == 0)
				count++;
	return count;
}