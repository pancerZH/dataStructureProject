#include <iostream>

using namespace std;

class Node {
public:
	Node(int num)
		:num(num), left(NULL), right(NULL), height(0) {}
	int num;
	Node* left;
	Node* right;
	int height;//记录节点的高度
};

class OrderTree {
public:
	OrderTree()
		:root(NULL), isEmpty(true) {}
	~OrderTree();
	Node* getRoot() { return root; }
	void renewRoot(Node* newRoot) { root = newRoot; }
	void releaseNode(Node*);
	bool insert(const int);//插入普通二叉查找树
	Node* insert(const int, Node*);//插入AVL树
	int getHeight(Node*);//获得节点高度，空节点高度为-1
	int max(const int, const int);
	Node* singleRotateWithLeft(Node*);//左子树单旋转
	Node* singleRotateWithRight(Node*);//右子树单旋转
	Node* doubleRotateWithLeft(Node*);//左子树双旋转
	Node* doubleRotateWithRight(Node*);//右子树双旋转
	bool searh(const int);
	void showAll(Node*);//以箭头格式打印二叉树
	void showAll(Node*, const int);//按结构打印二叉树
	bool isEmpty;//描述二叉树是否为空
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

Node* OrderTree::insert(const int num, Node* tree)
{
	if (tree == NULL)//将新节点插在空位置上
	{
		tree = new Node(num);
		if (tree == NULL)
		{
			cerr << "空间不足，插入失败！" << endl;
			return NULL;
		}
	}
	else if(num < tree->num)//插在左子树中
	{
		tree->left = insert(num, tree->left);
		if (getHeight(tree->left) - getHeight(tree->right) == 2)//破坏了AVL特性
		{
			/*新节点插入到了左儿子的左子树中，要求进行左子树单旋转*/
			if (num < tree->left->num)
				tree = singleRotateWithLeft(tree);
			/*新节点插入到了左儿子的右子树中，要求进行左子树双旋转*/
			else
				tree = doubleRotateWithLeft(tree);
		}
	}
	else if (num > tree->num)//插在右子树中
	{
		tree->right = insert(num, tree->right);
		if (getHeight(tree->right) - getHeight(tree->left) == 2)//破坏了AVL特性
		{
			/*新节点插入到了右儿子的右子树中，要求进行右子树单旋转*/
			if (num > tree->right->num)
				tree = singleRotateWithRight(tree);
			/*新节点插入到了右儿子的左子树中，要求进行右子树双旋转*/
			else
				tree = doubleRotateWithRight(tree);
		}
	}
	else//num已存在于AVL树中
	{
		cerr << "The input key(" << num << ") has been in!" << endl;
		return tree;
	}

	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;//更新根的高度
	isEmpty = false;//二叉排序树不再为空
	return tree;
}

int OrderTree::getHeight(Node* node)
{
	if (node == NULL)//空节点高度为-1
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

void OrderTree::showAll(Node* node, const int depth)
{
	if (node == NULL)
	{
		for (int i = depth;i > 0;--i)
			cout << '\t';
		cout << "空" << endl;
		return;
	}

	showAll(node->left, depth + 1);
	for (int i = depth;i > 0;--i)
		cout << '\t';
	cout << node->num << endl;
	showAll(node->right, depth + 1);
}