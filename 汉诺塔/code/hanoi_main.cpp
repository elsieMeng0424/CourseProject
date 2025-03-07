/* 2251079 国06 隋建政 */
#include <iostream>
#include <conio.h>
#include "hanoi.h"

using namespace std;

int t=1, col[3], pla[3][10],delay=0;

int main()
{
	int option,n=0,i,ret,k=0,x=0,m;
	char src=0, tmp=0, dst=0;
	while (1) {
		t = 1;
		delay = 0;
		k = 0;
		cct_cls();
		option = hanoi_menu();
		if (option == 0)
			break;
		if (option == 1 || option == 2 || option == 3 || option == 4 || option == 6 || option == 7 || option == 8||option==9) {
			shuru(&n, &src, &tmp, &dst, option);
			if (option != 6 && option != 7) {
				if (option == 4 || option == 8 || option == 9)
					print4(src, tmp, dst, n, option);
				else
					hanoi(n, src, tmp, dst, option);
			}
		}
		if (option == 5 || option == 6 || option == 7 ) {
			cct_cls();
			column();
		}
		if (option == 6 || option == 7)
			plate(n, src);

		if (option == 7)
			move(1, src, dst, n, 0, 1,0);
		if (option == 9) {
			while (!k) {
				m=mode9(n, option);
				if (m)
					break;
				for (i = 0; i < 10; i++) {
					k = 1;
					switch (dst) {
						case 'A':
							x = 0;
							break;
						case 'B':
							x = 1;
							break;
						case 'C':
							x = 2;
							break;
					}
					if (pla[col[x]][i] != n - i && n - i > 0) {
						k = 0;
						break;
					}
				}
			}
			for (i = 0; i < 7; i++)
				cout << endl;
			if (m)
				cout << "游戏中止!!!" << endl;
			else
			    cout << "游戏结束!!!" << endl;
			cout << endl;
		}
		if(option!=9)
		    for (i = 0; i < 10; i++)
			    cout << endl;
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		cout << "按回车继续";
		while (1) {
			ret = _getch();
			if (ret == 13)
				break;
		}
	}
	return 0;
}