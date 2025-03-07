/* 2251079 国06 隋建政 */
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;
#include "90-b2.h"

void output_balls(int ball[9][9], int row, int column)
{
	int i, j, x, y;
	cout << "  |";
	for (i = 1; i <= column; i++)
		cout << "  " << i;
	cout << endl;
	cout << "--+-";
	for (i = 1; i <= column; i++)
		cout << "---";
	cout << endl;
	for (i = 0; i < row; i++) {
		cout << char(i + 65) << " |";
		for (j = 0; j < column; j++) {
			if (ball[i][j] != 0) {
				cout << "  ";
				cct_getxy(x, y);
				cct_showch(x, y, char(ball[i][j] + 48), 14, ball[i][j], 1);
				cct_setcolor(0, 7);
			}
			else
				cout << "  " << ball[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void check_of_result(int row, int column, int way[100][2],char check[9][9])
{
	int i, j;
	for (i = 0; i < 100; i++) 
		check[way[i][0]][way[i][1]] = '*';
	cout << "查找结果数组:" << endl;
	cout << "  |";
	for (i = 1; i <= column; i++)
		cout << "  " << i;
	cout << endl;
	cout << "--+-";
	for (i = 1; i <= column; i++)
		cout << "---";
	cout << endl;
	for (i = 0; i < row; i++) {
		cout << char(i + 65) << " |";
		for (j = 0; j < column; j++) 
			cout << "  " << check[i][j];
		cout << endl;
	}
	cout << endl;
	cout << endl;
	cout << endl;
}

void show_of_way(int ball[9][9], char check[9][9],int row,int column)
{
	int i, j,x,y;
	cout << "移动路径<不同色标识>" << endl;
	cout << "  |";
	for (i = 1; i <= column; i++)
		cout << "  " << i;
	cout << endl;
	cout << "--+-";
	for (i = 1; i <= column; i++)
		cout << "---";
	cout << endl;
	for (i = 0; i < row; i++) {
		cout << char(i + 65) << " |";
		for (j = 0; j < column; j++)
			if (check[i][j] == '*') {
				cout << "  ";
				cct_getxy(x, y);
				cct_showch(x, y, char(ball[i][j] + 48), 14, 9, 1);
				cct_setcolor(0, 7);
			}
			else
				cout << "  " << ball[i][j];
		cout << endl;
	}
	cout << endl;
	cout << endl;
	cout << endl;
}

void print_frame_without_separation(int ball[9][9], int row, int column)
{
	int x, y, i, j,height=row+6;
	cct_cls();
	cct_setconsoleborder(35, height, 35, height);
	cct_setfontsize("新宋体",28+(row-7)*4, 0);
	cout << "屏幕："<<height<<"行35列" << endl;
	cct_getxy(x, y);
	cct_showstr(x, y, "╔", 15, 0, 1, 2);
	x += 2;
	cct_showstr(x, y, "═", 15, 0, column, 2*column);
	cct_getxy(x, y);
	cct_showstr(x, y, "╗", 15, 0, 1, 2);
	for (i = 0; i < row; i++) {
		cout << endl;
		cct_getxy(x, y);
		cct_showstr(x, y, "║", 15, 0, 1, 2);
		cct_setcolor(0, 7);
		for (j = 0; j < column; j++)
			cout << "  ";
		cct_getxy(x, y);
		cct_showstr(x, y, "║", 15, 0, 1, 2);
	}
	cout << endl;
	cct_getxy(x, y);
	cct_showstr(x, y, "╚", 15, 0, 1, 2);
	x += 2;
	cct_showstr(x, y, "═", 15, 0, column, 2 * column);
	cct_getxy(x, y);
	cct_showstr(x, y, "╝", 15, 0, 1, 2);
	cct_setcolor(0, 7);
}
   
void print_balls_without_separation(int ball[9][9],int row, int column)
{
	int x = 2, y = 2, i, j;
	for(i=0;i<row;i++,y++)
		for (j = 0, x = 2; j < column; j++, x+=2) {
			if (ball[i][j] == 0)
				cct_showstr(x, y, "  ", 15, 15, 1, 2);
			else
				cct_showstr(x, y, "○", ball[i][j]+7, 15, 1, 2);
		}
	cct_setcolor(0, 7);
	cout << endl;
	cout << endl;

}

void print_frame_with_separation(int ball[9][9],int row,int column,int k,int option)
{
	int x, y, i, j, height = 19 + (row - 7) * 2, wid = 35 + (column - 7) * 2;
	cct_cls();
	if (option != 7) {
		cct_setconsoleborder(wid, height, wid, height);
		cct_setfontsize("新宋体", 28 + (9 - row) * 4, 0);
		cout << "屏幕：" << height << "行" << wid << "列";
	}
	else {
		cct_setconsoleborder(70, 23, 70, 23);
		cct_setfontsize("新宋体", 24, 0);
		cout << "屏幕：23行70列";
	}
	if (k)
		cout << "(右键退出)";
	cout << endl;
	cct_getxy(x, y);
	cct_showstr(x, y, "╔", 15, 0, 1, 2);
	x += 2;
	cct_showstr(x, y, "═╦", 15, 0, column, 4 * column);
	cct_getxy(x, y);
	x -= 2;
	cct_showstr(x, y, "╗", 15, 0, 1, 2);
	for (i = 0; i < row; i++) {
		cout << endl;
		for (j = 0; j < column; j++) {
			cct_getxy(x, y);
			cct_showstr(x, y, "║", 15, 0, 1, 2);
			x += 2;
			cct_showstr(x, y, "  ", 15, 15, 1, 2);
			x += 2;
		}
		cct_getxy(x, y);
		cct_showstr(x, y, "║", 15, 0, 1, 2);
		y++;
		x = 0;
		cct_showstr(x, y, "╠", 15, 0, 1, 2);
		cct_getxy(x, y);
		cct_showstr(x, y, "═╬", 15, 0, column, 4 * column);
		cct_getxy(x, y);
		x -= 2;
		cct_showstr(x, y, "╣", 15, 0, 1, 2);
	}
	x = 0;
	cct_showstr(x, y, "╚", 15, 0, 1, 2);
	x += 2;
	cct_showstr(x, y, "═╩", 15, 0, column, 4 * column);
	cct_getxy(x, y);
	x -= 2;
	cct_showstr(x, y, "╝", 15, 0, 1, 2);
	cct_setcolor(0, 7);
}

void print_balls_with_separation(int ball[9][9],int row,int column)
{
	int x = 2, y = 2, i, j;
	for(i=0;i<row;i++,y+=2)
		for (j = 0,x=2; j < column; j++,x+=4)
			if(ball[i][j]!=0)
				cct_showstr(x, y, "○", ball[i][j]+7, 15, 1, 2);
			else
				cct_showstr(x, y, "  ", 15, 15, 1, 2);
	cct_setcolor(0, 7);
	x = 0;
	y = 2 * (row + 1);
	cct_gotoxy(x, y);
}

void read_position(int* p_MX, int* p_MY, int* p_MAction, int* p_keycode1, int* p_keycode2, int row, int column, int ball[9][9],int &x_src,int &x_dst,int &y_src,int &y_dst,int *p_num,int way[100][2])
{
	int x, y, i, j,color;
	while (1) {
		cct_enable_mouse();
		cct_read_keyboard_and_mouse(*p_MX, *p_MY, *p_MAction, *p_keycode1, *p_keycode2);
		x = 0;
		y = 2 * (row + 1);
		cct_gotoxy(x, y);
		if ((*p_MX + 2) % 4 == 1 && *p_MX >= 3 && *p_MX <= column * 4 - 1)
			(* p_MX)--;
		if (*p_MY % 2 == 0 && *p_MY >= 2 && *p_MY <= row * 2 && (*p_MX + 2) % 4 == 0 && *p_MX >= 2 && *p_MX <= column * 4 - 2) {
			cout << "当前光标[" << char(64 + *p_MY / 2) << "行" << (*p_MX + 2) / 4 << "列]";
			i = *p_MY / 2 - 1;
			j = (*p_MX + 2) / 4 - 1;
			if (*p_MAction == MOUSE_LEFT_BUTTON_CLICK && ball[i][j] != 0) {
				cct_showstr(*p_MX, *p_MY, "◎", ball[i][j] + 7, 15, 1, 2);
				cct_setcolor(0, 7);
				y_src = i;
				x_src = j;
				break;
			}
			if (*p_MAction == MOUSE_RIGHT_BUTTON_CLICK)
				break;
		}
	}
	if (*p_MAction != MOUSE_RIGHT_BUTTON_CLICK) {
		while (1) {
			cct_enable_mouse();
			cct_read_keyboard_and_mouse(*p_MX, *p_MY, *p_MAction, *p_keycode1, *p_keycode2);
			x = 0;
			y = 2 * (row + 1);
			cct_gotoxy(x, y);
			if ((*p_MX + 2) % 4 == 1 && *p_MX >= 3 && *p_MX <= column * 4 - 1)
				(*p_MX)--;
			if (*p_MY % 2 == 0 && *p_MY >= 2 && *p_MY <= row * 2 && (*p_MX + 2) % 4 == 0 && *p_MX >= 2 && *p_MX <= column * 4 - 2) {
				cout << "                                     ";
				cct_gotoxy(x, y);
				cout << "当前光标[" << char(64 + *p_MY / 2) << "行" << (*p_MX + 2) / 4 << "列]";
				i = *p_MY / 2 - 1;
				j = (*p_MX + 2) / 4 - 1;
				if (*p_MAction == MOUSE_RIGHT_BUTTON_CLICK)
					break;
				if (*p_MAction == MOUSE_LEFT_BUTTON_CLICK && ball[i][j] != 0) {
					cct_showstr((x_src + 1) * 4 - 2, (y_src + 1) * 2, "○", ball[y_src][x_src] + 7, 15, 1, 2);
					cct_showstr(*p_MX, *p_MY, "◎", ball[i][j] + 7, 15, 1, 2);
					cct_setcolor(0, 7);
					y_src = i;
					x_src = j;
					continue;
				}
				else if (*p_MAction == MOUSE_LEFT_BUTTON_CLICK && ball[i][j] == 0) {
					y_dst = i;
					x_dst = j;
					color = ball[y_src][x_src];
					if (search_way(ball, x_src, x_dst, y_src, y_dst, row, column, way, p_num)) {
						ball[y_src][x_src] = color;
						for (i = 0; i < row; i++)
							for (j = 0; j < column; j++)
								if (ball[i][j] == -1)
									ball[i][j] = 0;
						cct_gotoxy(0, 2 * (row + 1));
						cout << "[提示] 可以从[" << char(y_src + 65) << x_src + 1 << "]移动到[" << char(y_dst + 65) << x_dst + 1 << "]";
						break;
					}
					else {
						ball[y_src][x_src] = color;
						for (i = 0; i < row; i++)
							for (j = 0; j < column; j++)
								if (ball[i][j] == -1)
									ball[i][j] = 0;
						cct_gotoxy(0, 2 * (row + 1));
						cout << "[错误] 无法从[" << char(y_src + 65) << x_src + 1 << "]移动到[" << char(y_dst + 65) << x_dst + 1 << "]";
						continue;
					}
				}
			}
		}
	}
}

void move(int way[100][2],int x_src,int y_src,int ball[9][9])
{
	int i, start = 0,color;
	for (i = 0; i < 100; i++)
		if (way[i][0] != -1)
			start=i;
	for (i = start-1; i >= 0; i--) {
		cct_showstr((x_src + 1) * 4 - 2, (y_src + 1) * 2, "  ", 15, 15, 1, 2);
		color = ball[y_src][x_src];
		ball[y_src][x_src] = 0;
		if (way[i][0] - y_src == 1) {
			y_src++;
			ball[y_src][x_src] = color;
			cct_showstr((x_src + 1) * 4 - 2, (y_src + 1) * 2-1, "◎", ball[y_src][x_src]+7, 15, 1, 2);
			Sleep(80);
			cct_showstr((x_src + 1) * 4 - 2, (y_src + 1) * 2 - 1, "═", 15, 0, 1, 2);
			cct_showstr((x_src + 1) * 4 - 2, (y_src + 1) * 2 , "◎", ball[y_src][x_src] + 7, 15, 1, 2);
		}
		else if (way[i][0] - y_src == -1) {
			y_src--;
			ball[y_src][x_src] = color;
			cct_showstr((x_src + 1) * 4 - 2, (y_src + 1) * 2 + 1, "◎", ball[y_src][x_src] + 7, 15, 1, 2);
			Sleep(80);
			cct_showstr((x_src + 1) * 4 - 2, (y_src + 1) * 2 + 1, "═", 15, 0, 1, 2);
			cct_showstr((x_src + 1) * 4 - 2, (y_src + 1) * 2, "◎", ball[y_src][x_src] + 7, 15, 1, 2);
		}
		else if (way[i][1] - x_src == 1) {
			x_src++;
			ball[y_src][x_src] = color;
			cct_showstr(x_src  * 4, (y_src + 1) * 2, "◎", ball[y_src][x_src] + 7, 15, 1, 2);
			Sleep(80);
			cct_showstr(x_src * 4 , (y_src + 1) * 2, "║", 15, 0, 1, 2);
			cct_showstr((x_src + 1) * 4 - 2, (y_src + 1) * 2, "◎", ball[y_src][x_src] + 7, 15, 1, 2);
		}
		else if (way[i][1] - x_src == -1) {
			x_src--;
			ball[y_src][x_src] = color;
			cct_showstr((x_src + 1) * 4 , (y_src + 1) * 2 , "◎", ball[y_src][x_src] + 7, 15, 1, 2);
			Sleep(80);
			cct_showstr((x_src + 1) * 4 , (y_src + 1) * 2 , "║", 15, 0, 1, 2);
			cct_showstr((x_src + 1) * 4 - 2, (y_src + 1) * 2, "◎", ball[y_src][x_src] + 7, 15, 1, 2);
		}
		Sleep(80);
	}
	cct_setcolor(0, 7);
}

void print_score(int score,int row, int column)
{
	cct_showstr(column * 4 + 4, 1, "╔═════╗", 15, 0, 1, 14);
	cct_showstr(column * 4 + 4, 2, "║得分：    ║", 15, 0, 1, 14);
	cct_showint(column * 4 + 12, 2, score, 15, 0, 1);
	cct_showstr(column * 4 + 4, 3, "╚═════╝", 15, 0, 1, 14);
}

void print_prediction(int row, int column, int next1, int next2, int next3)
{
	cct_showstr(column * 4 + 4, 5, "╔═╦═╦═╗", 15, 0, 1, 14);
	cct_showstr(column * 4 + 4, 6, "║  ║  ║  ║", 15, 0, 1, 14);
	cct_showstr(column * 4 + 4, 7, "╚═╩═╩═╝", 15, 0, 1, 14);
	cct_showstr(column * 4 + 6, 6, "○", next1 + 7, 15, 1, 2);
	cct_showstr(column * 4 + 10, 6, "○", next2 + 7, 15, 1, 2);
	cct_showstr(column * 4 + 14, 6, "○", next3 + 7, 15, 1, 2);
}

void print_statistics(int ball[9][9], int row, int column,int elm[7])
{
	int i,sta[8],j;
	double per[8];
	cct_showstr(column * 4 + 4, 9, "╔════════════╗", 15, 0, 1, 28);
	for (i = 0; i < 8; i++) {
		cct_showstr(column * 4 + 4, 10 + i, "║  :00/( 0.00%) 消除-    ║", 15, 0, 1, 28);
		sta[i] = 0;
		per[i] = 0;
		if (i > 0)
			cct_showstr(column * 4 + 6, 10 + i, "○", i + 7, 15, 1, 2);
	}
	cct_showstr(column * 4 + 4, 18, "╚════════════╝", 15, 0, 1, 28);
	for(i=0;i<row;i++)
		for (j = 0; j < column; j++) {
			if (ball[i][j] == 0)
				sta[0]++;
			else
				sta[ball[i][j]]++;
		}
	for (i = 0; i < 8; i++) {
		per[i] = (double(sta[i]) / (row * column))*100;
		if (int(per[i] * 1000) % 10 >= 5)
			per[i] += 0.01;
		if (sta[i] > 9)
			cct_showint(column * 4 + 9, 10 + i, sta[i], 15, 0, 1);
		else
			cct_showint(column * 4 + 10, 10 + i, sta[i], 15, 0, 1);
		if(per[i]>=10)
			cct_showint(column * 4 + 13, 10 + i, int(per[i]), 15, 0, 1);
		else
			cct_showint(column * 4 + 14, 10 + i, int(per[i]), 15, 0, 1);
		if (int(per[i] * 100) % 100 >= 10)
			cct_showint(column * 4 + 16, 10 + i, int(int(per[i] * 100) % 100), 15, 0, 1);
		else
		    cct_showint(column * 4 + 17, 10 + i, int(int(per[i] * 100) % 100), 15, 0, 1);
		cct_showint(column * 4 + 26, 10 + i, elm[i], 15, 0, 1);
	}
	cct_setcolor(0, 7);
}