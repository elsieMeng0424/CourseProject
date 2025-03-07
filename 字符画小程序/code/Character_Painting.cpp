#define _CRT_SECURE_NO_WARNINGS
#include "Array.h"
#include "PicReader.h"
#include "FastPrinter.h"
#include <iostream>
#include <conio.h>
using namespace std;

void show(const char* name, int footstep)
{
	int x, y;
	PicReader imread;
	Array arr;
	imread.readPic(name);
	imread.getData(&x, &y, &arr);

	x = 2 * x / footstep;
	y = y / footstep;
	Array gray_pic(y, x);

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			int arr_i = i * footstep;
			int arr_j = j * footstep / 2;
			gray_pic[i][j] = int(int(arr[arr_i][arr_j][0]) * 299 + int(arr[arr_i][arr_j][1]) * 587 + int(arr[arr_i][arr_j][2]) * 114 + 500) / 1000;
		}
	}

	Array ave(y, x);
	int N = x * y;
	int count[256];
	double frq[256], frq_acu[256];
	for (int i = 0; i < 256; i++) {
		count[i] = 0;
		frq_acu[i] = 0;
	}
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			count[int(gray_pic[i][j])]++;
	for (int i = 0; i < 256; i++) {
		frq[i] = double(count[i]) / N;
	}
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j <= i; j++)
			frq_acu[i] += frq[j];
	}
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++) {
			ave[i][j] = int(frq_acu[int(gray_pic[i][j])] * 255);
			if (name == "classic_picture\\milkdrop.jpg") {
				if (ave[i][j] < 200)
					ave[i][j] = int(ave[i][j]) - 30;
				else if (ave[i][j] >= 200 && ave[i][j] < 235)
					ave[i][j] = int(ave[i][j]) - 50;
				if (ave[i][j] < 0)
					ave[i][j] = 0;
			}
		}

		
	char asciiStrength[] = { 'M', 'N', 'H', 'Q', '$', 'O', 'C', '?',
						'7', '>', '!', ':', '-', ';', '.' };
	// »Ò¶ÈÊý¾Ý
	char ch[2];
	COORD text;
	FastPrinter printer(x, y, 6);
	printer.cleanSrceen();
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++) {
			text.X = j;
			text.Y = i;
			if(name!="classic_picture\\compa.png")
			    ch[0] = asciiStrength[ave[i][j] / 18];
			else
				ch[0] = asciiStrength[gray_pic[i][j] / 18];
			ch[1] = '\0';
			printer.setText(text, ch, 0, 0, 0, 255, 255, 255);
		}
	printer.draw(true);
	system("pause");
}

int main()
{
	show("classic_picture\\lena1.jpg", 1);
	show("classic_picture\\lena.jpg", 3);
	show("classic_picture\\baboon.jpg", 4);
	show("classic_picture\\cameraman.jpg", 2);
	show("classic_picture\\peppers.jpg", 4);
	show("classic_picture\\woman.jpg", 4);
	show("classic_picture\\airplane.jpg", 4);
	show("classic_picture\\barbara.jpg", 5);
	show("classic_picture\\goldhill.jpg", 5);
	show("classic_picture\\compa.png", 2);
	show("classic_picture\\milkdrop.jpg", 4);
}