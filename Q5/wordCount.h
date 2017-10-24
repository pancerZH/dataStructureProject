#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define HASHSIZE 10
#define SPACE 32
#define END 0

/*============================以下为散列表的实现，它用于存放所有在文件中出现的单词及其出现次数=============================*/

class Node {
public:
	Node()
		:count(0), next(NULL) {};
	Node(const string word)
		:word(word), count(1), next(NULL) {}
	string word;
	int count;
	Node* next;
};

/*单词及出现次数使用分离链接散列表记录，以获得较快的查询速度，并且使用较小的空间*/

class Sepchain {
public:
	Sepchain(const int size);
	~Sepchain();
	int hash(const string);
	bool insert(const string);
	void showAll(const string);
private:
	int size;
	Node* head;
};

Sepchain::Sepchain(const int size)
	:size(size)
{
	head = new Node[size];
	if (head == NULL)
	{
		cerr << "空间不足！" << endl;
		exit(1);
	}
}

Sepchain::~Sepchain()
{
	for (int i = 0;i < size;++i)
	{
		Node* temp = head[i].next;
		while (temp != NULL)
		{
			Node* next = temp->next;
			delete temp;
			temp = next;
		}
	}

	delete[] head;
}

int Sepchain::hash(const string word)
{
	std::hash<string> hashStr;

	return (hashStr(word) % size);
}

bool Sepchain::insert(const string word)
{
	const int index = hash(word);

	Node* temp = &head[index];
	Node* previous;
	while (temp != NULL && temp->count != 0)//这个空间没有填入单词
	{
		if (temp->word == word)//找到了相同的单词
		{
			++(temp->count);
			return true;
		}
		else
		{
			previous = temp;
			temp = temp->next;
		}
	}

	if (temp == NULL)//向尾部插入新节点
	{
		temp = new Node(word);
		if (temp == NULL)
		{
			cerr << "空间不足！" << endl;
			exit(1);
		}
		previous->next = temp;
		return true;
	}
	else//将head[index]更新为word
	{
		temp->word = word;
		temp->count = 1;
		return true;
	}
}

void Sepchain::showAll(const string fileName)
{
	cout << "<<<<<<<<单词\t个数>>>>>>>>" << endl;

	int i = 0, alpha = 0, nonalpha = 0;
	while (i < size)
	{
		Node* temp = &head[i];
		while (temp != NULL && temp->count != 0)
		{
			cout << "\t" << temp->word << "\t" << temp->count << "\t" << endl;
			if (isalpha(temp->word[0]))
				alpha += temp->count;
			else
				nonalpha += temp->count;
			temp = temp->next;
		}
		++i;
	}

	cout << endl ;
	cout << ">>>>>>>>" << fileName << "的单词总数为" << alpha << "个" << endl << endl;
	cout << ">>>>>>>>" << fileName << "的非单词总数为" << nonalpha << "个" << endl << endl;
}

/*============================以上为散列表的实现，它用于存放所有在文件中出现的单词及其出现次数=============================*/

/*=============================以下为链表的实现，它用于存放某一单词在某一行中出现的位置和次数==============================*/

class Chain {
public:
	Chain(const int pos)
		:pos(pos), next(NULL) {}
	int pos;
	Chain* next;
};

class Linklist {
public:
	Linklist(const string word, const int line)
		:word(word), head(NULL), size(0), line(line) {}
	~Linklist();
	bool insert(const int);
	void checkWord(const string);
	void showAll(const string, const char);
private:
	string word;
	Chain* head;
	int size;//代表链表中元素数量
	int line;//代表是第line行的统计结果
};

Linklist::~Linklist()
{
	Chain* temp;
	while (head != NULL)
	{
		temp = head->next;
		delete head;
		head = temp;
	}
}

bool Linklist::insert(const int pos)
{
	Chain* temp = head;
	Chain* previous = temp;
	while (temp != NULL)
	{
		previous = temp;
		temp = temp->next;
	}

	temp = new Chain(pos);
	if (temp == NULL)
	{
		cerr << "空间不足！" << endl;
		exit(1);
	}
	if (previous != NULL)
		previous->next = temp;
	else
		head = temp;
	size += 1;//链表中元素数量加1
	return true;
}

void Linklist::checkWord(const string line)
{
	int pos = 0;
	while ((pos = line.find(word, pos)) != -1)//查找word下一个出现的位置
	{
		char wordHead;
		if (pos != 0)
			wordHead = line[pos - 1];
		else
			wordHead = SPACE;
		char wordTail = line[pos + word.length()];

		if (wordHead == SPACE && (wordTail == SPACE || wordTail == END))//保证搜索到的是一个单词而不是单词的一部分字母
		{
			insert(pos);
		}
		pos += word.length();
	}
}

void Linklist::showAll(const string fileName, const char choice)
{
	if (choice == 'a')//查询单词出现的次数
		cout << endl << "单词" << word << "在文本文件" << fileName << "中共出现" << size << "次" << endl;
	else//查询单词的位置
	{
		if (size == 0)//word在本行未出现
			return;

		cout << "行号：" << line << "，次数：" << size << "，起始位置分别为：第";
		Chain* temp = head;
		while (temp != NULL)
		{
			cout << temp->pos + 1;
			temp = temp->next;
			if (temp != NULL)
				cout << "，";
		}
		cout << "个字符" << endl;
	}
}

/*=============================以上为链表的实现，它用于存放某一单词在某一行中出现的位置和次数==============================*/

/*===============================以下为文件类的实现，包含了建立文件和读取文件进行统计的功能================================*/

class Paragraph {
public:
	Paragraph();
	~Paragraph() { delete table; }
	bool buildPara();//建立文本文档
	bool countWords();//统计文档中的单词
	bool wordInLine();//统计某一行中的单词
private:
	int tableSize;// 记录table中的元素个数
	Sepchain* table;
};

Paragraph::Paragraph()
	:tableSize(0)
{
	table = new Sepchain(HASHSIZE);
	if (table == NULL)
	{
		cerr << "空间不足！" << endl;
		exit(1);
	}
}

bool Paragraph::buildPara()
{
	string fileName;
	cout << "输入要建立的文件名：";
	getline(cin, fileName);

	ofstream inFile;
	inFile.open(fileName, ios::trunc);
	if (inFile.is_open() == false)
	{
		cerr << "创建文件失败！" << endl;
		exit(2);
	}

	char c = 'n';
	while (c == 'n')
	{
		string line;
		cout << "请输入一行文本：";
		getline(cin, line);
		inFile << line << endl;

		cout << "结束输入吗？y or n";
		cin >> c;
		getchar();
	}
	inFile.close();

	return true;
}

bool Paragraph::countWords()
{
	string fileName;
	cout << "请输入文件名：";
	getline(cin, fileName);

	ifstream outFile;
	outFile.open(fileName, ios::_Nocreate);
	if (outFile.is_open() == false)
	{
		cerr << "文件不存在或打开失败！" << endl;
		exit(2);
	}

	if (tableSize != 0)//清除旧表
	{
		delete table;
		table = new Sepchain(HASHSIZE);//重新建立散列表
		if (table == NULL)
		{
			cerr << "空间不足！" << endl;
			exit(1);
		}
	}

	string word;
	while (outFile >> word)
	{
		if (!table->insert(word))//插入失败
			return false;
		else
			++tableSize;
	}

	outFile.close();
	table->showAll(fileName);
	return true;
}

bool Paragraph::wordInLine()
{
	char choice;
	cout << "======================================" << endl;
	cout << "===文本文件单词字串的定位统计及定位===" << endl;
	cout << "======================================" << endl;
	cout << "         a.      单词出现次数         " << endl << endl << endl;
	cout << "         b.      单词出现位置         " << endl << endl;
	cout << "======================================" << endl;
	cout << "请输入a或b：";
	cin >> choice;
	getchar();

	string fileName;
	cout << "请输入文件名：";
	getline(cin, fileName);

	ifstream outFile;
	outFile.open(fileName, ios::_Nocreate);
	if (outFile.is_open() == false)
	{
		cerr << "文件不存在或打开失败！" << endl;
		exit(2);
	}

	string word;
	cout << "请输入要统计的单词：";
	getline(cin, word);

	string line;
	if (choice == 'a')
	{
		Linklist* list = new Linklist(word, 0);
		while (getline(outFile, line))
			list->checkWord(line);
		list->showAll(fileName, choice);
	}
	else
	{
		int i = 0;//i用于表示第i行
		while (getline(outFile, line))
		{
			++i;
			Linklist* list = new Linklist(word, i);
			list->checkWord(line);
			list->showAll(fileName, choice);
			delete list;
		}
	}

	outFile.close();
	return true;
}

/*===============================以上为文件类的实现，包含了建立文件和读取文件进行统计的功能================================*/