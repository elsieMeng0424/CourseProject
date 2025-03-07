#include "head.h"

int main()
{
	while (true)
	{
		FileCompress test;
		string name;
		cout << "#########################################################################" << endl;
		cout << "请输入要操作的文件名（无需加尾缀，可供选择的文件名有test1，test2，test3）：";
		cin >> name;
		if (name != "test1" && name != "test2" && name != "test3")
		{
			cout << "无效的文件名, 请重新输入\n" << endl;
			continue;
		}
		test.Init(name);

		string OPTR;
		cout << "请输入操作(Compress, Uncompress, Exit)：" ;
		cin >> OPTR;
		if (OPTR == "Compress")
			test.Compress();
		else if (OPTR == "Uncompress")
			test.UnCompress();
		else if (OPTR == "Exit")
			break;
		else
			cout << "无效的操作" << endl;
	}

	return 0;
}