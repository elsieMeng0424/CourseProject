/* 2251079 ��06 �彨�� */
#include <iostream>
#include <conio.h>
using namespace std;

int hanoi_menu()
{
	int option;
	cout << "---------------------------------" << endl;
	cout << "1.������" << endl;
	cout << "2.������(������¼)" << endl;
	cout << "3.�ڲ�������ʾ(����)" << endl;
	cout << "4.�ڲ�������ʾ(����+����)" << endl;
	cout << "5.ͼ�ν�-Ԥ��-������Բ��" << endl;
	cout << "6.ͼ�ν�-Ԥ��-����ʼ���ϻ�n������" << endl;
	cout << "7.ͼ�ν�-Ԥ��-��һ���ƶ�" << endl;
	cout << "8.ͼ�ν�-�Զ��ƶ��汾" << endl;
	cout << "9.ͼ�ν�-��Ϸ��" << endl;
	cout << "0.�˳�" << endl;
	cout << "---------------------------------" << endl;
	cout << "[��ѡ��:]";
	while(1) {
		option = _getch();
		if (option >= '0' && option <= '9') {
			cout << char(option) << endl;
			break;
		}
	}
	cout << endl;
	return option-48;
}