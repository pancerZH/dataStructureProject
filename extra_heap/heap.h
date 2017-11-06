#include <iostream>
#include <stack>

using namespace std;

/*===========================================以下为二叉堆的实现===========================================*/

class Heap {
public:
	Heap(const int);//堆数组将从1开始记录数据
	~Heap();
	bool extendSpace();//实现倍增数组
	void swap(int&, int&);
	bool insert(const int);
	int popMin();
	void percolateUp(const int);//上滤
	void percolateDown(const int);//下滤
	void showHeap();
	void showNum(const int, const int);
private:
	int size;
	int length;
	int* head;
};

Heap::Heap(const int size)//要求size大于0
	:size(size), length(1)
{
	head = new int[size + 1];
	if (head == NULL)
	{
		cerr << "内存空间不足！" << endl;
		exit(1);
	}
	head[0] = INT_MIN;//头结点为标记

	cout << "请输入堆中数字！" << endl;
	int i = size, num;
	while (i--)
	{
		cin >> num;
		while (cin.fail())
		{
			cerr << "请输入整数范围内的数字！" << endl;
			cin.clear();
			cin.ignore();
			cin >> num;
		}
		head[length] = num;
		++length;
	}

	/*将无序树转变为二叉堆*/
	for (int i = size / 2;i > 0;--i)
		percolateDown(i);
}

Heap::~Heap()
{
	delete[] head;
	head = NULL;
}

bool Heap::extendSpace()
{
	size *= 2;
	int* temp = new int[size + 1];
	if (temp == NULL)
	{
		cerr << "内存空间不足！" << endl;
		exit(1);
	}

	for (int i = 1;i < length;++i)
		temp[i] = head[i];
	
	delete[] head;
	head = temp;
	return true;
}

void Heap::swap(int& num1, int& num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}

bool Heap::insert(const int num)
{
	if (length == size + 1)//已装满数组
		extendSpace();

	head[length] = num;
	percolateUp(length);
	++length;
	return true;
}

int Heap::popMin()
{
	if (length <= 1)
	{
		cerr << "二叉堆中没有元素！" << endl;
		return INT_MIN;
	}

	int min = head[1];
	head[1] = head[length - 1];
	--length;
	percolateDown(1);

	return min;
}

void Heap::percolateUp(const int index)
{
	for (int i = index;head[i] < head[i / 2];i /= 2)
		swap(head[i], head[i / 2]);
}

void Heap::percolateDown(const int index)
{
	for (int i = index, child = 2 * index;child < length;i = child)
	{
		/*找到两个儿子（如果有）中较小的那个用于比较*/
		if (child + 1 < length && head[child + 1] < head[child])
			++child;
		/*如果儿子小于父亲，则进行下滤，否则结束整个循环*/
		if (head[child] < head[i])
			swap(head[child], head[i]);
		else
			break;
	}
}

void Heap::showHeap()
{
	showNum(1, 0);
}

void Heap::showNum(const int index, const int depth)
{
	if (index >= length)
	{
		int i = depth;
		while (i--)
			cout << '\t';
		cout << "空" << endl;
		return;
	}

	showNum(index * 2, depth + 1);
	int i = depth;
	while (i--)
		cout << '\t';
	cout << head[index] << endl;
	showNum(index * 2 + 1, depth + 1);
}

/*===========================================以上为二叉堆的实现===========================================*/

/*===========================================以下为左式堆的实现===========================================*/

class Node {
public:
	Node(const int elem)
		:left(NULL), right(NULL), elem(elem), Npl(0) {}
	Node* left;
	Node* right;
	int elem;
	int Npl;
};

class LeftistHeap {
	/*要求左儿子的Npl大于等于右子树的Npl*/
public:
	LeftistHeap(const int);
	~LeftistHeap();
	void deleteNode(Node*&);
	void insert(Node*);
	void updateNpl(Node*);
	void show();
	void showNum(Node*, const int);
	Node* merge(Node*, Node*);
	Node* mergeTwoParts(Node*, Node*);
	void updateRoot(Node* newRoot) { root = newRoot; }
	Node* getRoot() { return root; }
private:
	Node* root;
};

LeftistHeap::LeftistHeap(const int size)//要求size大于0
	:root(NULL)
{
	cout << "请输入堆中数字！" << endl;
	int i = size, num;
	while (i--)
	{
		cin >> num;
		while (cin.fail())
		{
			cerr << "请输入整数范围内的数字！" << endl;
			cin.clear();
			cin.ignore();
			cin >> num;
		}

		Node* node = new Node(num);
		if (node == NULL)
		{
			cerr << "内存空间不足！" << endl;
			exit(1);
		}
		insert(node);
	}
}

LeftistHeap::~LeftistHeap()
{
	deleteNode(root);
}

void LeftistHeap::deleteNode(Node*& node)
{
	if (node == NULL || int(node) == 0xdddddddd)
		return;

	deleteNode(node->left);
	deleteNode(node->right);
	delete node;
	node = NULL;
}

void LeftistHeap::insert(Node* node)
{
	if (root == NULL)
	{
		root = node;
		return;
	}

	stack<Node*> path;
	Node* temp = root;
	while (temp->left != NULL && temp->right != NULL && node->elem > temp->elem)
	{
		path.push(temp);//将插入经过的路径放入栈中
		temp = temp->left;//优先插入到左子树，除非右儿子为空
	}
	if (temp->elem > node->elem)
	{
		node->left = temp;
		if (!path.empty())
			path.top()->left = node;
		else
			root = node;
	}
	else if (temp->left == NULL)
		temp->left = node;
	else
		temp->right = node;

	/*更新插入路径上各节点的高度*/
	for (size_t i = 0;i < path.size();++i)
	{
		updateNpl(path.top());
		path.pop();
	}
}

void LeftistHeap::updateNpl(Node* node)
{
	if (node == NULL)
		return;
	else if (node->left == NULL && node->right == NULL)
	{
		node->Npl = 0;
		return;
	}
	else if (node->left != NULL && node->right == NULL)
	{
		node->Npl = node->left->Npl + 1;
		return;
	}
	else if (node->left == NULL && node->right != NULL)
	{
		node->Npl = node->right->Npl + 1;
		return;
	}
	else
	{
		int min = node->left->Npl;
		if (min > node->right->Npl)
			min = node->right->Npl;
		node->Npl = min + 1;
		return;
	}
}

void LeftistHeap::show()
{
	showNum(root, 0);
}

void LeftistHeap::showNum(Node* node, const int depth)
{
	int i = depth;
	if (node == NULL)
	{
		while (i--)
			cout << '\t';
		cout << "空" << endl;
		return;
	}

	showNum(node->right, depth + 1);
	while (i--)
		cout << '\t';
	cout << node->elem << endl;
	showNum(node->left, depth + 1);
}

Node* LeftistHeap::merge(Node* node1, Node* node2)
{
	if (node1 == NULL)
		return node2;
	if (node2 == NULL)
		return node1;
	if (node1->elem > node2->elem)//将根元素大的插入根元素小的
		return mergeTwoParts(node2, node1);
	else
		return mergeTwoParts(node1, node2);
}

/*保证master和servant都不为NULL*/
Node* LeftistHeap::mergeTwoParts(Node* master, Node* servant)
{
	if (master->left == NULL)//master是独立点
		master->left = servant;
	else
	{
		master->right = merge(master->right, servant);
		/*如果合并后不符合左式堆的性质，交换左右子树*/
		if (master->left->Npl < master->right->Npl)
		{
			Node* temp = master->right;
			master->right = master->left;
			master->left = temp;
		}

		updateNpl(master);//更新Npl
	}

	return master;
}