#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define HASHSIZE 10
#define SPACE 32
#define END 0

/*============================����Ϊɢ�б��ʵ�֣������ڴ���������ļ��г��ֵĵ��ʼ�����ִ���=============================*/

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

/*���ʼ����ִ���ʹ�÷�������ɢ�б��¼���Ի�ýϿ�Ĳ�ѯ�ٶȣ�����ʹ�ý�С�Ŀռ�*/

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
		cerr << "�ռ䲻�㣡" << endl;
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
	while (temp != NULL && temp->count != 0)//����ռ�û�����뵥��
	{
		if (temp->word == word)//�ҵ�����ͬ�ĵ���
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

	if (temp == NULL)//��β�������½ڵ�
	{
		temp = new Node(word);
		if (temp == NULL)
		{
			cerr << "�ռ䲻�㣡" << endl;
			exit(1);
		}
		previous->next = temp;
		return true;
	}
	else//��head[index]����Ϊword
	{
		temp->word = word;
		temp->count = 1;
		return true;
	}
}

void Sepchain::showAll(const string fileName)
{
	cout << "<<<<<<<<����\t����>>>>>>>>" << endl;

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
	cout << ">>>>>>>>" << fileName << "�ĵ�������Ϊ" << alpha << "��" << endl << endl;
	cout << ">>>>>>>>" << fileName << "�ķǵ�������Ϊ" << nonalpha << "��" << endl << endl;
}

/*============================����Ϊɢ�б��ʵ�֣������ڴ���������ļ��г��ֵĵ��ʼ�����ִ���=============================*/

/*=============================����Ϊ�����ʵ�֣������ڴ��ĳһ������ĳһ���г��ֵ�λ�úʹ���==============================*/

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
	int size;//����������Ԫ������
	int line;//�����ǵ�line�е�ͳ�ƽ��
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
		cerr << "�ռ䲻�㣡" << endl;
		exit(1);
	}
	if (previous != NULL)
		previous->next = temp;
	else
		head = temp;
	size += 1;//������Ԫ��������1
	return true;
}

void Linklist::checkWord(const string line)
{
	int pos = 0;
	while ((pos = line.find(word, pos)) != -1)//����word��һ�����ֵ�λ��
	{
		char wordHead;
		if (pos != 0)
			wordHead = line[pos - 1];
		else
			wordHead = SPACE;
		char wordTail = line[pos + word.length()];

		if (wordHead == SPACE && (wordTail == SPACE || wordTail == END))//��֤����������һ�����ʶ����ǵ��ʵ�һ������ĸ
		{
			insert(pos);
		}
		pos += word.length();
	}
}

void Linklist::showAll(const string fileName, const char choice)
{
	if (choice == 'a')//��ѯ���ʳ��ֵĴ���
		cout << endl << "����" << word << "���ı��ļ�" << fileName << "�й�����" << size << "��" << endl;
	else//��ѯ���ʵ�λ��
	{
		if (size == 0)//word�ڱ���δ����
			return;

		cout << "�кţ�" << line << "��������" << size << "����ʼλ�÷ֱ�Ϊ����";
		Chain* temp = head;
		while (temp != NULL)
		{
			cout << temp->pos + 1;
			temp = temp->next;
			if (temp != NULL)
				cout << "��";
		}
		cout << "���ַ�" << endl;
	}
}

/*=============================����Ϊ�����ʵ�֣������ڴ��ĳһ������ĳһ���г��ֵ�λ�úʹ���==============================*/

/*===============================����Ϊ�ļ����ʵ�֣������˽����ļ��Ͷ�ȡ�ļ�����ͳ�ƵĹ���================================*/

class Paragraph {
public:
	Paragraph();
	~Paragraph() { delete table; }
	bool buildPara();//�����ı��ĵ�
	bool countWords();//ͳ���ĵ��еĵ���
	bool wordInLine();//ͳ��ĳһ���еĵ���
private:
	int tableSize;// ��¼table�е�Ԫ�ظ���
	Sepchain* table;
};

Paragraph::Paragraph()
	:tableSize(0)
{
	table = new Sepchain(HASHSIZE);
	if (table == NULL)
	{
		cerr << "�ռ䲻�㣡" << endl;
		exit(1);
	}
}

bool Paragraph::buildPara()
{
	string fileName;
	cout << "����Ҫ�������ļ�����";
	getline(cin, fileName);

	ofstream inFile;
	inFile.open(fileName, ios::trunc);
	if (inFile.is_open() == false)
	{
		cerr << "�����ļ�ʧ�ܣ�" << endl;
		exit(2);
	}

	char c = 'n';
	while (c == 'n')
	{
		string line;
		cout << "������һ���ı���";
		getline(cin, line);
		inFile << line << endl;

		cout << "����������y or n";
		cin >> c;
		getchar();
	}
	inFile.close();

	return true;
}

bool Paragraph::countWords()
{
	string fileName;
	cout << "�������ļ�����";
	getline(cin, fileName);

	ifstream outFile;
	outFile.open(fileName, ios::_Nocreate);
	if (outFile.is_open() == false)
	{
		cerr << "�ļ������ڻ��ʧ�ܣ�" << endl;
		exit(2);
	}

	if (tableSize != 0)//����ɱ�
	{
		delete table;
		table = new Sepchain(HASHSIZE);//���½���ɢ�б�
		if (table == NULL)
		{
			cerr << "�ռ䲻�㣡" << endl;
			exit(1);
		}
	}

	string word;
	while (outFile >> word)
	{
		if (!table->insert(word))//����ʧ��
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
	cout << "===�ı��ļ������ִ��Ķ�λͳ�Ƽ���λ===" << endl;
	cout << "======================================" << endl;
	cout << "         a.      ���ʳ��ִ���         " << endl << endl << endl;
	cout << "         b.      ���ʳ���λ��         " << endl << endl;
	cout << "======================================" << endl;
	cout << "������a��b��";
	cin >> choice;
	getchar();

	string fileName;
	cout << "�������ļ�����";
	getline(cin, fileName);

	ifstream outFile;
	outFile.open(fileName, ios::_Nocreate);
	if (outFile.is_open() == false)
	{
		cerr << "�ļ������ڻ��ʧ�ܣ�" << endl;
		exit(2);
	}

	string word;
	cout << "������Ҫͳ�Ƶĵ��ʣ�";
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
		int i = 0;//i���ڱ�ʾ��i��
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

/*===============================����Ϊ�ļ����ʵ�֣������˽����ļ��Ͷ�ȡ�ļ�����ͳ�ƵĹ���================================*/