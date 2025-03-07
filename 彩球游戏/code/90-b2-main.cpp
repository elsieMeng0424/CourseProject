/* 2251079 国06 隋建政 */
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
#include "90-b2.h"

int menu()
{
	int option;
	cout << "--------------------------------------------" << endl;
	cout << "1.内部数组，随机生成初始5个球" << endl;
	cout << "2.内部数组，随机生成60%的球，寻找移动路径" << endl;
	cout << "3.内部数组，完整版" << endl;
	cout << "4.画出n*n的框架（无分割线），随机显示5个球" << endl;
	cout << "5.画出n*n的框架（有分割线），随机显示5个球" << endl;
	cout << "6.n*n的框架，60%的球，支持鼠标，完成一次移动" << endl;
	cout << "7.cmd图形界面完整版" << endl;
	cout << "0.退出" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[请选择:]";
	do {
		option = _getch();
	} while (option < '0' || option>'7');
	cout << char(option) << endl;
	Sleep(200);
	return option - 48;
}

void option1(int *p_row,int*p_column,int ball[9][9])
{
	input(p_row, p_column);
	cout << endl;
	input_five_balls(ball, *p_row, *p_column);
	cout << "初始数组:" << endl;
	output_balls(ball, *p_row, *p_column);
}

void option2(int ball[9][9],int *p_row,int *p_column,char check[9][9],int way[100][2])
{
	input(p_row, p_column);
	cout << endl;
	int num_src = 1, num_dst = 1, x_src, x_dst, y_src, y_dst, k = 0, num = 0, i, j, next1 = 0, next2 = 0, next3 = 0;
	int * p_num_src = &num_src, * p_num_dst = &num_dst, * p_num = &num, * p_next1 = &next1, * p_next2 = &next2, * p_next3 = &next3;
	char src = 'A', dst = 'A';
	char* p_src = &src, * p_dst = &dst;
	input_60_percent(ball, *p_row, *p_column);
	cout << "当前数组:" << endl;
	output_balls(ball, *p_row, *p_column);
	prediction(p_next1, p_next2, p_next3,2);
	output2(ball, *p_row, *p_column, p_num_src, p_num_dst, p_src, p_dst);
	x_src = num_src - 1;
	x_dst = num_dst - 1;
	y_src = src - 65;
	y_dst = dst - 65;
	k = ball[y_src][x_src];
	if (search_way(ball, x_src, x_dst, y_src, y_dst, *p_row, *p_column, way, p_num)) {
		cout << endl;
		cout << endl;
		ball[y_src][x_src] = k;
		for (i = 0; i < *p_row; i++)
			for (j = 0; j < *p_column; j++)
				if (ball[i][j] == -1)
					ball[i][j] = 0;
		check_of_result(*p_row, *p_column, way, check);
		show_of_way(ball, check, *p_row, *p_column);
	}
	else
		cout << "无法找到移动路径" << endl;
}

void option3(int ball[9][9], int* p_row, int* p_column, char check[9][9], int way[100][2])
{
	input(p_row, p_column);
	cout << endl;
	int num_src = 1, num_dst = 1, x_src, x_dst, y_src, y_dst, k = 0, num = 0, i, j, next1 = 0, next2 = 0, next3 = 0,
		score=0,score_once=0,del[100][2],elm[8]={0,0,0,0,0,0,0,0};
	int* p_num_src = &num_src, * p_num_dst = &num_dst, * p_num = &num, * p_next1 = &next1, * p_next2 = &next2, * p_next3 = &next3,*p_score_once=&score_once;
	char src = 'A', dst = 'A';
	char* p_src = &src, * p_dst = &dst;
	input_five_balls(ball, *p_row, *p_column);
	while (1) {
		for (i = 0; i < 100; i++) {
			del[i][0] = -1;
			del[i][1] = -1; 
			way[i][0] = -1;
			way[i][1] = -1;
		}
		score_once = 0;
		cout << "当前数组:" << endl;
		output_balls(ball, *p_row, *p_column);
		prediction(p_next1, p_next2, p_next3,3);
		if (!check_of_end(ball, *p_row, *p_column)) {
			cout << "无空位可移动，游戏结束！" << endl;
			break;
		}
		output2(ball, *p_row, *p_column, p_num_src, p_num_dst, p_src, p_dst);
		x_src = num_src - 1;
		x_dst = num_dst - 1;
		y_src = src - 65;
		y_dst = dst - 65;
		k = ball[y_src][x_src];
		if (search_way(ball, x_src, x_dst, y_src, y_dst, *p_row, *p_column, way, p_num)) {
			cout << endl;
			cout << endl;
			ball[y_dst][x_dst] = k;
			for (i = 0; i < *p_row; i++)
				for (j = 0; j < *p_column; j++)
					if (ball[i][j] == -1)
						ball[i][j] = 0;
			input_next(ball, *p_row, *p_column, *p_next1, *p_next2, *p_next3,check_of_end(ball,*p_row,*p_column));
			check_score(ball, *p_row, *p_column, p_score_once, del);
			del_score(ball, del,elm);
			cout << "移动后的数组<不同色标识>:" << endl;
			output_balls(ball, *p_row, *p_column);
			score += score_once;
			cout << endl;
			cout << "本次得分:" << score_once << "总得分:" << score << endl;
			cout << endl;
		}
		else {
			cout << "无法找到移动路径" << endl;
			cout << endl;
		}
	}
}

void option4(int ball[9][9], int *p_row, int *p_column)
{
	int ret = 0;
	input(p_row, p_column);
	cout << endl;
	input_five_balls(ball, *p_row, *p_column);
	cout << "初始数组:" << endl;
	output_balls(ball, *p_row, *p_column);
	cout << "按回车键显示图形...";
	while (ret != 13)
		ret = _getch();
	print_frame_without_separation(ball, *p_row, *p_column);
	print_balls_without_separation(ball, *p_row, *p_column);
}

void option5(int ball[9][9],int *p_row,int *p_column)
{
	int ret = 0;
	input(p_row, p_column);
	cout << endl;
	input_five_balls(ball, *p_row, *p_column);
	cout << "初始数组:" << endl;
	output_balls(ball, *p_row, *p_column);
	cout << "按回车键显示图形...";
	while (ret != 13)
		ret = _getch();
	print_frame_with_separation(ball, *p_row, *p_column,0,5);
	print_balls_with_separation(ball, *p_row, *p_column);
}

void option6(int ball[9][9], int* p_row, int* p_column, char check[9][9], int way[100][2])
{
	int MX = 2, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0,x_src,x_dst,y_src,y_dst,num=0;
	int* p_MX = &MX, * p_MY = &MY, * p_MAction = &MAction, * p_keycode1 = &keycode1, * p_keycode2 = &keycode2, * p_num = &num;
	input(p_row, p_column);
	cout << endl;
	input_60_percent(ball, *p_row, *p_column);
	print_frame_with_separation(ball, *p_row, *p_column,1,6);
	print_balls_with_separation(ball, *p_row, *p_column);
	cct_setcursor(CURSOR_INVISIBLE);
	read_position(p_MX, p_MY, p_MAction, p_keycode1, p_keycode2, *p_row, *p_column, ball, x_src, x_dst, y_src, y_dst, p_num, way);
	move(way, x_src, y_src, ball);
	cct_gotoxy(0, 2 * (*p_row + 1));
}

void option7(int ball[9][9], int* p_row, int* p_column, int way[100][2])
{
	int i,  del[100][2], score_once = 0, score = 0, next1 = 0, next2 = 0, next3 = 0, elm[8], 
		MX = 2, MY = 0, MAction = 0, keycode1 = 0, keycode2 = 0, x_src, x_dst, y_src, y_dst, num = 0,color;
	int* p_next1 = &next1, * p_next2 = &next2, * p_next3 = &next3, * p_MX = &MX, * p_MY = &MY, * p_MAction = &MAction,
		* p_keycode1 = &keycode1, * p_keycode2 = &keycode2, * p_num = &num, * p_score_once = &score_once;
	for (i = 0; i < 8; i++)
		elm[i] = 0;
	input(p_row, p_column);
	cout << endl;
	input_five_balls(ball, *p_row, *p_column);
	print_frame_with_separation(ball, *p_row, *p_column, 1, 7);
	while (1) {
		elm[0] = 0;
		cct_gotoxy(0, 2 * (*p_row + 1));
		cout << "                            ";
		score_once = 0;
		num = 0;
		MAction = 0;
		for (i = 0; i < 100; i++) {
			del[i][0] = -1;
			del[i][1] = -1;
			way[i][0] = -1;
			way[i][1] = -1;
		}
		input_next(ball, *p_row, *p_column, *p_next1, *p_next2, *p_next3, check_of_end(ball, *p_row, *p_column));
		prediction(p_next1, p_next2, p_next3,7);
		print_balls_with_separation(ball, *p_row, *p_column);
		print_score(score, *p_row, *p_column);
		print_prediction(*p_row, *p_column, next1, next2, next3);
		print_statistics(ball, *p_row, *p_column, elm);
		if (!check_of_end(ball, *p_row, *p_column)) {
			cct_gotoxy(0, 2 * (*p_row + 1));
			cct_setcolor(0, 7);
			cout << "游戏结束" << endl;
			break;
		}
		cct_setcursor(CURSOR_INVISIBLE);
		read_position(p_MX, p_MY, p_MAction, p_keycode1, p_keycode2, *p_row, *p_column, ball, x_src, x_dst, y_src, y_dst, p_num, way);
		if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
			cct_gotoxy(0, 2 * (*p_row + 1));
			cct_setcolor(0, 7);
			break;
		}
		color = ball[y_src][x_src];
		move(way, x_src, y_src, ball);
		ball[y_dst][x_dst] = color;
		check_score(ball, *p_row, *p_column, p_score_once, del);
		del_score(ball, del,elm);
		score += score_once;
	}
}

int main()
{
	int option,row=0,column=0,ball[9][9],i,j,way[100][2], cols = 120, lines = 35, buffer_cols = 120, buffer_lines = 1000;
	int* p_row = &row, * p_column = &column;
	char check[9][9];
	cct_setcolor(0, 7);
	while (1) {
		cct_setconsoleborder(cols, lines, buffer_cols, buffer_lines);
		cct_setfontsize("", 16, 8);
		cct_cls();
		for (i = 0; i < 9; i++)
			for (j = 0; j < 9; j++) {
				ball[i][j] = 0;
				check[i][j] = '0';
			}
		for (i = 0; i < 100; i++) {
			way[i][0] = -1;
			way[i][1] = -1;
		}
		option = menu();
		if (option != 0) {
			cct_cls();
			if (option == 1)
				option1(p_row, p_column, ball);
			if (option == 2) {
				option2(ball, p_row, p_column, check, way);
				cout << endl;
			}
			if (option == 3)
				option3(ball, p_row, p_column, check, way);
			if (option == 4)
				option4(ball, p_row, p_column);
			if (option == 5)
				option5(ball, p_row, p_column);
			if (option == 6)
				option6(ball, p_row, p_column, check, way);
			if (option == 7)
				option7(ball, p_row, p_column, way);
		}
		else {
			cct_gotoxy(0, 20);
			break;
		}
		End();
	}
}