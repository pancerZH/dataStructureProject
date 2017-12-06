#include <iostream>

using namespace std;

class Node {
public:
	Node(int num)
		:num(num), left(NULL), right(NULL), height(0) {}
	int num;
	Node* left;
	Node* right;
	int height;//��¼�ڵ�ĸ߶�
};

class OrderTree {
public:
	OrderTree()
		:root(NULL), isEmpty(true) {}
	~OrderTree();
	Node* getRoot() { return root; }
	void renewRoot(Node* newRoot) { root = newRoot; }
	void releaseNode(Node*);
	bool insert(const int);//������ͨ���������
	Node* insert(const int, Node*);//����AVL��
	int getHeight(Node*);//��ýڵ�߶ȣ��սڵ�߶�Ϊ-1
	int max(const int, const int);
	Node* singleRotateWithLeft(Node*);//����������ת
	Node* singleRotateWithRight(Node*);//����������ת
	Node* doubleRotateWithLeft(Node*);//������˫��ת
	Node* doubleRotateWithRight(Node*);//������˫��ת
	bool searh(const int);
	void showAll(Node*);//�Լ�ͷ��ʽ��ӡ������
	void showAll(Node*, const int);//���ṹ��ӡ������
	bool isEmpty;//�����������Ƿ�Ϊ��
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

Node* OrderTree::insert(const int num, Node* tree)
{
	if (tree == NULL)//���½ڵ���ڿ�λ����
	{
		tree = new Node(num);
		if (tree == NULL)
		{
			cerr << "�ռ䲻�㣬����ʧ�ܣ�" << endl;
			return NULL;
		}
	}
	else if(num < tree->num)//������������
	{
		tree->left = insert(num, tree->left);
		if (getHeight(tree->left) - getHeight(tree->right) == 2)//�ƻ���AVL����
		{
			/*�½ڵ���뵽������ӵ��������У�Ҫ���������������ת*/
			if (num < tree->left->num)
				tree = singleRotateWithLeft(tree);
			/*�½ڵ���뵽������ӵ��������У�Ҫ�����������˫��ת*/
			else
				tree = doubleRotateWithLeft(tree);
		}
	}
	else if (num > tree->num)//������������
	{
		tree->right = insert(num, tree->right);
		if (getHeight(tree->right) - getHeight(tree->left) == 2)//�ƻ���AVL����
		{
			/*�½ڵ���뵽���Ҷ��ӵ��������У�Ҫ���������������ת*/
			if (num > tree->right->num)
				tree = singleRotateWithRight(tree);
			/*�½ڵ���뵽���Ҷ��ӵ��������У�Ҫ�����������˫��ת*/
			else
				tree = doubleRotateWithRight(tree);
		}
	}
	else//num�Ѵ�����AVL����
	{
		cerr << "The input key(" << num << ") has been in!" << endl;
		return tree;
	}

	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;//���¸��ĸ߶�
	isEmpty = false;//��������������Ϊ��
	return tree;
}

int OrderTree::getHeight(Node* node)
{
	if (node == NULL)//�սڵ�߶�Ϊ-1
		return -1;
	else
		return node->height;
}

int OrderTree::max(const int num1, const int num2)
{
	if (num1 > num2)
		return num1;
	else
		return num2;
}

Node* OrderTree::singleRotateWithLeft(Node* tree)
{
	Node* newTree = tree->left;
	tree->left = newTree->right;
	newTree->right = tree;

	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
	newTree->height = max(getHeight(newTree->left), getHeight(newTree->right)) + 1;

	return newTree;
}

Node* OrderTree::singleRotateWithRight(Node* tree)
{
	Node* newTree = tree->right;
	tree->right = newTree->left;
	newTree->left = tree;

	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
	newTree->height = max(getHeight(newTree->left), getHeight(newTree->right)) + 1;

	return newTree;
}

Node* OrderTree::doubleRotateWithLeft(Node* tree)
{
	tree->left = singleRotateWithRight(tree->left);
	return singleRotateWithLeft(tree);
}

Node* OrderTree::doubleRotateWithRight(Node* tree)
{
	tree->right = singleRotateWithLeft(tree->right);
	return singleRotateWithRight(tree);
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

void OrderTree::showAll(Node* node, const int depth)
{
	if (node == NULL)
	{
		for (int i = depth;i > 0;--i)
			cout << '\t';
		cout << "��" << endl;
		return;
	}

	showAll(node->left, depth + 1);
	for (int i = depth;i > 0;--i)
		cout << '\t';
	cout << node->num << endl;
	showAll(node->right, depth + 1);
}