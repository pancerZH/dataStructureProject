#include <iostream>

using namespace std;

/*==================================以下为分离链接散列表的实现==================================*/

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
	head = (Node*)malloc(sizeof(Node) * size);//申请size个Node大小的空间
	if (head == NULL)
	{
		cerr << "内存不足！" << endl;
		return;
	}

	for (int i = 0;i < size;++i)//将这size个Node初始化
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
		cerr << "内存不足！" << endl;
		return false;
	}

	int index = hash(num);
	Node* temp = &head[index];
	while (temp->num != num && temp->next != NULL)//防止表中元素重复
		temp = temp->next;
	if (temp->num == num)//出现了重复
	{
		delete addNode;
		return true;
	}
	temp->next = addNode;

	return true;
}

bool Sepchain::removeNum(const int num)
{
	int index = hash(num);
	Node* temp = &head[index];
	Node* previous = temp;
	while (temp != NULL && temp->num != num)
	{
		previous = temp;
		temp = temp->next;
	}

	if (temp == NULL)//未找到要删除的元素
		return false;
	else//找到了要删除的元素
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

/*==================================以上为分离链接散列表的实现==================================*/