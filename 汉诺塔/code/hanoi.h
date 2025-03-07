#pragma once
/* 2251079 ¹ú06 Ëå½¨Õþ */
#include "cmd_console_tools.h"
int hanoi_menu();
void shuru(int *n, char *src, char *tmp, char *dst,int option);
void hanoi(int n, char src, char tmp, char dst,int option);
void print4(char src, char tmp, char dst, int n, int option);
void column();
void plate(int n,char src);
void move(int n,char src,char dst,int num_src,int num_dst,int k,int delay);
int mode9(int n,int option);