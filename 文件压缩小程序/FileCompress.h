#ifndef FILECOMPRESS_H
#define FILECOMPRESS_H
#define OK 1
#define ERROR 0


class FileCompress {
private:
	string filename;
	string compressedname;
	string uncompressedname;
	string ReadFile();
	void TextExtract(char* text, int* weight, int& num, string Text);
	char BtoD(string str);
	string StrCodeTrans(string strcode, int &k);
	string CtoB(string str);
public:
	FileCompress(string s1 = "", string s2 = "", string s3 = "") :filename(s1), compressedname(s2), uncompressedname(s3) {};
	void Init(string name);
	int Compress();
	int UnCompress();
	void ViewOriginal();
};

void FileCompress::Init(string name)
{
	filename = name + ".txt";
	compressedname = name + "_compressed.txt";
	uncompressedname = name + "_uncompressed.txt";
}

string FileCompress::ReadFile()
{
	string Text;
	fstream file;
	file.open(filename);
	while (!file.eof())
	{
		char ch;
		file >> noskipws >> ch;
		Text = Text + ch;
	}
	Text = Text.substr(0, int(Text.size()) - 1);
	file.close();
	return Text;
}

void FileCompress::TextExtract(char* text, int* weight, int& num, string Text)
{
	for (int i = 0; i < int(Text.size()); i++)
	{
		char ch = Text[i];
		for (int j = 0; j < 128; j++)
		{
			if (text[j] == '\0')
			{
				text[j] = ch;
				weight[j] = 1;
				break;
			}
			if (text[j] == ch)
			{
				weight[j]++;
				break;
			}
		}
	}

	num = 0;
	for (int i = 0; i < 128; i++)
	{
		if (text[i] == '\0')
			break;
		num++;
	}
}

char FileCompress::BtoD(string str)
{
	int result = 0, c = 1;
	for (int i = int(str.size()) - 1; i >= 0; i--)
	{
		result += (str[i] - '0') * c;
		c *= 2;
	}
	return char(result);
}

string FileCompress::StrCodeTrans(string strcode, int &k)
{
	string result = "";
	int NeedAdd = (8 - int(strcode.size()) % 8) % 8;
	for (int i = 0; i < NeedAdd; i++)
	{
		strcode = strcode + '0';
	}
	k = NeedAdd;
	int pos = 0;
	while (pos < int(strcode.size()))
	{
		string str = strcode.substr(pos, 8);
		result = result + BtoD(str);
		pos += 8;
	}
	return result;
}

int FileCompress::Compress()
{
	//读取原文本
	string Text = ReadFile();

	char text[128] = { '\0' };
	int weight[128] = { -1 };
	int num = 0;
	TextExtract(text, weight, num, Text);

	//创建哈夫曼树
	int OriginalNum = int(Text.size()) * 8;
	HuffmanTree tree;
	tree.CreateHTree(weight, num, text);
	cout << "\n哈夫曼树创建完成\n";
	tree.CreateCodetable();
	cout << "\n编码表创建完成\n";

	//文件压缩
	int k;
	cout << "\n文件开始压缩\n压缩中。。。\n";
	string strcode = tree.Encode(Text);
	string strcompressed = StrCodeTrans(strcode, k);
	ofstream CompressedFile;
	CompressedFile.open(compressedname, ios::binary);
	CompressedFile << num << '\n';
	CompressedFile << k << '\n';
	for (int i = 0; i < num; i++)
		CompressedFile << text[i];
	CompressedFile << '\n';
	for (int i = 0; i < num; i++)
		CompressedFile << weight[i] << ' ';
	CompressedFile << '\n';
	CompressedFile.write(strcompressed.c_str(), int(strcompressed.size()));
	CompressedFile.close();

	ifstream ReadSize;
	ReadSize.open(compressedname, ios::binary);
	ReadSize.seekg(0, ios::end);
	int CompressedNum = int(ReadSize.tellg()) * 8;
	ReadSize.close();

	cout << "压缩完成" << endl;
	cout << "压缩率为：" << double(CompressedNum) / double(OriginalNum) * 100 << "%\n";
	return OK;
}

string FileCompress::CtoB(string str)
{
	string result = "";
	for (int i = 0; i < int(str.size()); i++) {
		bitset<8> bs4(str[i]);
		for (int j = 7; j >= 0; j--)
		{
			char ch = bs4[j];
			result = result + char(ch + '0');
		}
	}
	return result;
}

int FileCompress::UnCompress()
{
	int k;
	cout << "\n文件开始解压\n解压中。。。\n";
	string str2 = "";
	ifstream file;
	file.open(compressedname, ios::binary);
	int num;
	char chf;
	file >> num;
	file >> k;
	file >> noskipws >> chf;
	char text[128] = { '\0' };
	int weight[128] = { -1 };
	for (int i = 0; i < num; i++)
		file >> noskipws >> text[i];
	file >> noskipws >> chf;
	for (int i = 0; i < num; i++)
	{
		string numstr = "";
		while (true) {
			char numch;
			file >> noskipws >> numch;
			if (numch == ' ')
			{
				weight[i] = atoi(numstr.c_str());
				break;
			}
			numstr = numstr + numch;
		}
	}

	char ch;
	if (!file.get(ch))
		cout << "读取不成功" << endl;
	while (file.get(ch))
	{
		str2 = str2 + ch;
	}
	file.close();
	string strcodebinary = CtoB(str2);
	string strToDecode = strcodebinary.substr(0, int(strcodebinary.size()) - k);

	HuffmanTree tree;
	tree.CreateHTree(weight, num, text);
	tree.CreateCodetable();
	string result = tree.Decode(strToDecode);
	ofstream ofile;
	ofile.open(uncompressedname);
	ofile << result;
	ofile.close();
	cout << "解压完成" << endl;
	return OK;
}

void FileCompress::ViewOriginal()
{
	string str = ReadFile();
	cout << str << endl;
}

#endif
