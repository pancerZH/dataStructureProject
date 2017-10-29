#include <iostream>

using namespace std;

class Node {
public:
	Node(int num)
		:num(num), left(NULL), right(NULL) {}
	int num;
	Node* left;
	Node* right;
};

class OrderTree {
public:
	OrderTree()
		:root(NULL), isEmpty(true) {}
	~OrderTree();
	Node* getRoot() { return root; }
	void releaseNode(Node*);
	bool insert(const int);
	bool searh(const int);
	void showAll(Node*);
	bool isEmpty;
private:
	Node* root;
};

OrderTree::~OrderTree()
{
	releaseNode(root);
}

void OrderTree::releaseNode(Node* node)
{
	if (node == NULL)
		return;
	else
	{
		releaseNode(node->left);
		releaseNode(node->right);
		delete node;
	}
}

bool OrderTree::insert(const int num)
{
	Node* newNode = new Node(num);
	if (newNode == NULL)
	{
		cerr << "�ռ䲻�㣬����ʧ�ܣ�" << endl;
		return false;
	}

	Node* temp = root;
	while (temp != NULL)//��ʵ��ֻ�ڵ�һ���ж�ʱ��Ч
	{
		if (num < temp->num)//���������С�ڽڵ��ֵ����������������
		{
			if (temp->left != NULL)//����������ӱȽ�
				temp = temp->left;
			else//�˽ڵ�������ӣ��򽫲���Ľڵ���Ϊ�����
			{
				temp->left = newNode;
				return true;
			}
		}
		else if (num > temp->num)//����������
		{
			if (temp->right != NULL)//�������Ҷ��ӱȽ�
				temp = temp->right;
			else//�˽ڵ����Ҷ��ӣ��򽫲���Ľڵ���Ϊ�Ҷ���
			{
				temp->right = newNode;
				return true;
			}
		}
		else
		{
			cerr << "The input key(" << num << ") has been in!" << endl;
			return false;
		}
	}

	root = newNode;//����˴���˵��rootΪNULL
	isEmpty = false;//��������������Ϊ��
	return true;
}

bool OrderTree::searh(const int num)
{
	Node* temp = root;
	while (temp != NULL)
	{
		if (num < temp->num)//��ѯԪ��С�ڽڵ��ֵ��������ѯ��������
			temp = temp->left;
		else if (num > temp->num)//������ѯ������
			temp = temp->right;
		else//�ҵ���
		{
			cout << "search success!" << endl;
			return false;
		}
	}

	cout << num << " not exist!" << endl;//����˴���˵��δ�ҵ�Ԫ��
	return false;
}

void OrderTree::showAll(Node* node)
{
	if (node == NULL)
		return;

	showAll(node->left);
	cout << node->num << "->";
	showAll(node->right);
}