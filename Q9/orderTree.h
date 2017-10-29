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
		cerr << "空间不足，插入失败！" << endl;
		return false;
	}

	Node* temp = root;
	while (temp != NULL)//事实上只在第一次判断时有效
	{
		if (num < temp->num)//插入的数字小于节点的值，插入其左子树中
		{
			if (temp->left != NULL)//继续与左儿子比较
				temp = temp->left;
			else//此节点无左儿子，则将插入的节点作为左儿子
			{
				temp->left = newNode;
				return true;
			}
		}
		else if (num > temp->num)//插入右子树
		{
			if (temp->right != NULL)//继续与右儿子比较
				temp = temp->right;
			else//此节点无右儿子，则将插入的节点作为右儿子
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

	root = newNode;//到达此处则说明root为NULL
	isEmpty = false;//二叉排序树不再为空
	return true;
}

bool OrderTree::searh(const int num)
{
	Node* temp = root;
	while (temp != NULL)
	{
		if (num < temp->num)//查询元素小于节点的值，继续查询其左子树
			temp = temp->left;
		else if (num > temp->num)//继续查询右子树
			temp = temp->right;
		else//找到了
		{
			cout << "search success!" << endl;
			return false;
		}
	}

	cout << num << " not exist!" << endl;//到达此处，说明未找到元素
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