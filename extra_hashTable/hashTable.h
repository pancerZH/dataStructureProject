#include <iostream>

using namespace std;

/*==================================����Ϊ��������ɢ�б��ʵ��==================================*/

class Node {
public:
	Node(const int num)
		:num(num), next(NULL) {}
	int num;
	Node* next;
};

class Sepchain {
public:
	Sepchain(const int);
	~Sepchain();
	int hash(const int num) { return (num % 10); }
	bool addNum(const int);
	bool removeNum(const int);
	void showAll();
private:
	Node* head;
	int size;
};

Sepchain::Sepchain(const int size)
	:size(size)
{
	head = (Node*)malloc(sizeof(Node) * size);//����size��Node��С�Ŀռ�
	if (head == NULL)
	{
		cerr << "�ڴ治�㣡" << endl;
		return;
	}

	for (int i = 0;i < size;++i)//����size��Node��ʼ��
	{
		head[i].num = size;
		head[i].next = NULL;
	}
}

Sepchain::~Sepchain()
{
	for (int i = 0;i < size;++i)
	{
		Node* currentNode = head[i].next;
		while (currentNode != NULL)
		{
			Node* temp = currentNode;
			currentNode = currentNode->next;
			delete temp;
			temp = NULL;
		}
	}
	free(head);
}

bool Sepchain::addNum(const int num)
{
	Node* addNode = new Node(num);
	if (addNode == NULL)
	{
		cerr << "�ڴ治�㣡" << endl;
		return false;
	}

	const int index = hash(num);
	Node* temp = &head[index];
	while (temp->num != num && temp->next != NULL)//��ֹ����Ԫ���ظ�
		temp = temp->next;
	if (temp->num == num)//�������ظ�
	{
		delete addNode;
		return true;
	}
	temp->next = addNode;

	return true;
}

bool Sepchain::removeNum(const int num)
{
	const int index = hash(num);
	Node* temp = &head[index];
	Node* previous = temp;
	while (temp != NULL && temp->num != num)
	{
		previous = temp;
		temp = temp->next;
	}

	if (temp == NULL)//δ�ҵ�Ҫɾ����Ԫ��
		return false;
	else//�ҵ���Ҫɾ����Ԫ��
	{
		previous->next = temp->next;
		delete temp;
		temp = NULL;
		return true;
	}
}

void Sepchain::showAll()
{
	for (int i = 0;i < size;++i)
	{
		cout << i << " : ";
		Node* temp = head[i].next;
		while (temp != NULL)
		{
			cout << temp->num << " --> ";
			temp = temp->next;
		}
		cout << "NULL" << endl;
	}
}

/*==================================����Ϊ��������ɢ�б��ʵ��==================================*/

/*==================================����Ϊ���Ŷ�ַɢ�б��ʵ��==================================*/

class Block {
public:
	Block() :isEmpty(true) {}
	bool isEmpty;
	int num;
};

class Openchain {
public:
	Openchain(const int);
	~Openchain() { delete[] head; }
	int hash(const int num) { return (num%size); }
	int hash2(const int num) { return (R - num%R); }
	bool lineDetect(const int);
	bool squareDetect(const int);
	bool doubleHash(const int);
	void showAll();
private:
	int size;
	Block* head;
	int R;
};

Openchain::Openchain(const int size)
	:size(size), R(7)
{
	//head = (Block*)malloc(sizeof(Block)*size);
	//�������ַ����޷���ʼ��Block����
	head = new Block[10];
	if (head == NULL)
	{
		cerr << "�ڴ治�㣡" << endl;
		return;
	}
}

bool Openchain::lineDetect(const int num)
{
	const int index = hash(num);
	for (int temp = index;temp + 1 != index;++temp)
	{
		if (temp == size)//Խ��֮�󷵻�0��
			temp = 0;
		
		if (head[temp].isEmpty == true)
		{
			head[temp].isEmpty = false;
			head[temp].num = num;
			return true;
		}
	}
	return false;//������
}

bool Openchain::squareDetect(const int num)
{
	const int index = hash(num);
	if (head[index].isEmpty == true)
	{
		head[index].isEmpty = false;
		head[index].num = num;
		return true;
	}

	int temp = -1 ,count = 1;
	while (temp != index)
	{
		temp = index + count*count;
		++count;

		if (temp >= size)//Խ��֮���ۻ����
			temp -= size;

		if (head[temp].isEmpty == true)
		{
			head[temp].isEmpty = false;
			head[temp].num = num;
			return true;
		}
	}
	return false;
}

bool Openchain::doubleHash(const int num)
{
	const int index = hash(num);
	if (head[index].isEmpty == true)
	{
		head[index].isEmpty = false;
		head[index].num = num;
		return true;
	}

	const int gap = hash2(num);
	for (int i = 1, temp = index + i*gap;temp != index;temp = index + i*gap)
	{
		if (temp >= size)//Խ��֮���ۻ����
			temp -= size;

		if (head[temp].isEmpty == true)
		{
			head[temp].isEmpty = false;
			head[temp].num = num;
			return true;
		}
	}
	return false;
}

void Openchain::showAll()
{
	for (int i = 0;i < size;++i)
	{
		cout << i << " : ";
		if (head[i].isEmpty == false)
			cout << head[i].num << endl;
		else
			cout << "NULL" << endl;
	}
}