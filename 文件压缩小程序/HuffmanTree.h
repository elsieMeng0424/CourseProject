#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

struct HNode
{
	int weight; // 结点权值
	int parent; // 双亲数组下标
	int LChild; // 左孩子数组下标
	int RChild; // 右孩子数组下标
};

struct HCode
{
	char data{};
	string code;
};

class HuffmanTree {
private:
	HNode* HTree; // 哈夫曼树
	HCode* HCodeTable; // 存储编码表
	int N; // 叶子结点数量
	void code(int i, string newcode); // 递归函数，对第i个结点编码
	void SelectMin(int* px, int* py, int i);
public:
	void CreateHTree(int weight[], int n, char ch[]); // 创建哈夫曼树
	void CreateCodetable(); // 创建编码表
	void Encode(char* strcode, char* strch); // 编码
	string Encode(string strch); // 编码
	void Decode(char* s, char* d); // 解码
	string Decode(string strcode); // 解码
	void DisplayTable();
	void DisplayTree();
	~HuffmanTree();
};

void HuffmanTree::SelectMin(int* px, int* py, int num)
{
	int min1 = -1;
	int pmin = 0;
	for (int i = 0; i < num; i++)
	{
		if (HTree[i].parent == -1 && min1 == -1) {
			min1 = HTree[i].weight;
			pmin = i;
		}
		if (HTree[i].weight < min1 && HTree[i].parent == -1)
		{
			pmin = i;
			min1 = HTree[i].weight;
		}
	}
	*px = pmin;
	min1 = -1;
	for (int i = 0; i < num; i++)
	{
		if (HTree[i].parent == -1 && min1 == -1 && i != *px) {
			min1 = HTree[i].weight;
			pmin = i;
		}
		if (HTree[i].weight < min1 && HTree[i].parent == -1 && i != *px)
		{
			pmin = i;
			min1 = HTree[i].weight;
		}
	}
	*py = pmin;
}

void HuffmanTree::CreateHTree(int weight[], int n, char ch[])
{
	N = n;
	HCodeTable = new HCode[N];
	HTree = new HNode[2 * N - 1];
	for (int i = 0; i < N; i++)
	{
		HTree[i].weight = weight[i];
		HTree[i].LChild = HTree[i].RChild = HTree[i].parent = -1;
		HCodeTable[i].data = ch[i];
	}
	int x, y;
	for (int i = n; i < 2 * N - 1; i++)
	{
		SelectMin(&x, &y, i);
		HTree[x].parent = HTree[y].parent = i;
		HTree[i].weight = HTree[x].weight + HTree[y].weight;
		HTree[i].LChild = x;
		HTree[i].RChild = y;
		HTree[i].parent = -1;
	}
}

void HuffmanTree::code(int i, string newcode)
{
	if (HTree[i].LChild == -1)
	{
		HCodeTable[i].code = newcode;
		return;
	}
	code(HTree[i].LChild, newcode + "0");
	code(HTree[i].RChild, newcode + "1");
}

void HuffmanTree::CreateCodetable()
{
	code(2 * N - 2, "");
}

void HuffmanTree::Encode(char* strcode, char* strch)
{
	string str = "";
	while (*strch != '\0')
	{
		int j = 0;
		while (HCodeTable[j].data != *strch)
		{
			j++;
			if (j >= N)throw"error!";
		}
		strch++;
		str = str + HCodeTable[j].code;
	}
	strcpy(strcode, str.c_str());
}

string HuffmanTree::Encode(string strch)
{
	string str = "";
	for (int i = 0; i < int(strch.size()); i++)
	{
		int j = 0;
		while (HCodeTable[j].data != strch[i])
		{
			j++;
			if (j >= N)throw"error!";
		}
		str = str + HCodeTable[j].code;
	}
	return str;
}

void HuffmanTree::Decode(char* strcode, char* strch)
{
	while (*strcode != '\0')
	{
		int parent = 2 * N - 2;
		while (HTree[parent].LChild != -1)
		{
			if (*strcode == '0')
				parent = HTree[parent].LChild;
			else
				parent = HTree[parent].RChild;
			strcode++;
		}
		*strch = HCodeTable[parent].data;
		strch++;
	}
	*strch = '\0';
}

string HuffmanTree::Decode(string strcode)
{
	string str = "";
	int i = 0;
	while (i < int(strcode.size()))
	{
		int parent = 2 * N - 2;
		while (HTree[parent].LChild != -1)
		{
			if (strcode[i] == '0')
				parent = HTree[parent].LChild;
			else
				parent = HTree[parent].RChild;
			i++;
		}
		str = str + HCodeTable[parent].data;
	}
	return str;
}

void HuffmanTree::DisplayTable()
{
	for (int i = 0; i < N; i++)
	{
		cout << "data:" << HCodeTable[i].data << ' ' << "code:" << HCodeTable[i].code << endl;
	}
}

void HuffmanTree::DisplayTree()
{
	for (int i = 0; i < 2 * N - 1; i++)
	{
		cout << "LChild:" << HTree[i].LChild << ' ' << "RChild:" << HTree[i].RChild << ' '
			<< "parent:" << HTree[i].parent << ' ' << "weight:" << HTree[i].weight << endl;
	}
}

HuffmanTree::~HuffmanTree()
{
	delete[]HTree;
	delete[]HCodeTable;
}

#endif
