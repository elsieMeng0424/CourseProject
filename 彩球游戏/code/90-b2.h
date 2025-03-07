#pragma once
/* 2251079 ¹ú06 Ëå½¨Õþ */
#include "cmd_console_tools.h"
void input(int *p_row,int *p_column);
void input_five_balls(int ball[9][9], int row, int column);
void output_balls(int ball[9][9], int row, int column);
void End();
void input_60_percent(int ball[9][9], int row, int column);
void output2(int ball[9][9],int row, int column,int *p_num_src,int*p_num_dst,char*p_src,char*p_dst);
int search_way(int ball[9][9], int x_src, int x_dst, int y_src, int y_dst, int row, int column, int way[100][2], int* p_num);
void check_of_result(int row, int column, int way[100][2],char check[9][9]);
void show_of_way(int ball[9][9], char check[9][9], int row, int column);
void input_next(int ball[9][9], int row, int column, int next1, int next2, int next3, int n);
void check_score(int ball[9][9], int row, int column, int* p_score_once,int del[100][2]);
void del_score(int ball[9][9], int del[100][2],int elm[8]);
void prediction(int* p_next1, int* p_next2, int* p_next3,int option);
int check_of_end(int ball[9][9], int row, int column);
void print_frame_without_separation(int ball[9][9], int row, int column);
void print_balls_without_separation(int ball[9][9], int row, int column);
void print_frame_with_separation(int ball[9][9], int row, int column,int k,int option);
void print_balls_with_separation(int ball[9][9], int row, int column);
void read_position(int* p_MX, int* p_MY, int* p_MAction, int* p_keycode1, int* p_keycode2, int row, int column,int ball[9][9], int& x_src, int& x_dst, int& y_src, int& y_dst,int *p_num,int way[100][2]);
void move(int way[100][2], int x_src, int y_src, int ball[9][9]);
void print_score(int score, int row, int column);
void print_prediction(int row, int column, int next1, int next2, int next3);
void print_statistics(int ball[9][9], int row, int column,int elm[7]);