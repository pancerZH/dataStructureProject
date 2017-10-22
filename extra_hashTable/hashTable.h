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

	int index = hash(num);
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
	int index = hash(num);
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