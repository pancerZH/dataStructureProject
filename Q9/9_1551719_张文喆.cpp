#include "orderTree.h"

bool checkIfThereIsATree(OrderTree*);
void buildTree(OrderTree*);
void buildTreeAVL(OrderTree*);
void insert(OrderTree*);
void insertAVL(OrderTree*);
void search(OrderTree*);

int main()
{
	cout << "**\t\t二叉排序树\t\t**" << endl;
	cout << "==========================================" << endl;
	cout << "**\t\t0 --- 建立AVL树\t\t**" << endl;
	cout << "**\t\t1 --- 建立二叉排序树\t**" << endl;
	cout << "**\t\t2 --- 插入元素\t\t**" << endl;
	cout << "**\t\t3 --- 查询元素\t\t**" << endl;
	cout << "**\t\t4 --- 退出程序\t\t**" << endl;
	cout << "==========================================" << endl;

	OrderTree* tree = NULL;
	bool isAVL;
	while (1)
	{
		int operation = 4;
		cout << endl << "Please select:";
		cin >> operation;

		switch (operation)
		{
		case 0:
			if (!checkIfThereIsATree(tree))
			{
				tree = new OrderTree();
				if (tree == NULL)
				{
					cerr << "内存空间不足!" << endl;
					exit(1);
				}
				buildTreeAVL(tree);
				isAVL = true;
			}
			break;
		case 1:
			if (!checkIfThereIsATree(tree))
			{
				tree = new OrderTree();
				if (tree == NULL)
				{
					cerr << "内存空间不足!" << endl;
					exit(1);
				}
				buildTree(tree);
				isAVL = false;
			}
			break;
		case 2:
			if (!isAVL)
				insert(tree);
			else
				insertAVL(tree);
			break;
		case 3:
			search(tree);
			break;
		default:
			return 0;
		}
	}
}

bool checkIfThereIsATree(OrderTree* tree)
{
	if (tree == NULL)
		return false;

	if (!tree->isEmpty)//检查是否已经建立过一棵树
	{
		cout << "There is already a Bsort_Tree" << endl;
		cout << "Do you want to delete it?(y/n)";
		char ch;
		cin >> ch;
		cin.clear();

		if (ch == 'y' || ch == 'Y')
		{
			delete tree;
			tree = NULL;
			cout << "The old Tree has been deleted!" << endl;
			return false;
		}
		else
		{
			cout << "I will not delete the old Tree" << endl;
			return true;
		}
	}
	return false;//没有建立过树
}

void buildTree(OrderTree* tree)
{
	cout << "Please input key to create Bsort_Tree:" << endl;
	int num;
	cin >> num;
	if (cin.fail())
	{
		cerr << "输入失败，请输入整数！" << endl;
		cin.clear();
		cin.ignore();
		return;
	}
	while (num != 0)//0是输入结束的标记
	{
		tree->insert(num);
		cin >> num;
		if (cin.fail())
		{
			cerr << "输入失败，请输入整数！" << endl;
			cin.clear();
			cin.ignore();
			return;
		}
	}

	tree->showAll(tree->getRoot());
	cout << endl << endl;
	tree->showAll(tree->getRoot(), 0);
	cout << endl;
}

void buildTreeAVL(OrderTree* tree)
{
	cout << "Please input key to create AVL_Tree:" << endl;
	int num;
	cin >> num;
	if (cin.fail())
	{
		cerr << "输入失败，请输入整数！" << endl;
		cin.clear();
		cin.ignore();
		return;
	}
	while (num != 0)//0是输入结束的标记
	{
		tree->renewRoot(tree->insert(num, tree->getRoot()));
		cin >> num;
		if (cin.fail())
		{
			cerr << "输入失败，请输入整数！" << endl;
			cin.clear();
			cin.ignore();
			return;
		}
	}

	tree->showAll(tree->getRoot());
	cout << endl << endl;
	tree->showAll(tree->getRoot(), 0);
	cout << endl;
}

void insert(OrderTree* tree)
{
	if (tree == NULL)
	{
		cerr << "请先建立二叉树！" << endl;
		return;
	}

	cout << "Please input key which inserted:";
	int num;
	cin >> num;
	if (cin.fail())
	{
		cerr << "请输入整数！" << endl;
		cin.clear();
		cin.ignore();
		return;
	}
	tree->insert(num);

	tree->showAll(tree->getRoot());
	cout << endl << endl;
	tree->showAll(tree->getRoot(), 0);
	cout << endl;
}

void insertAVL(OrderTree* tree)
{
	if (tree == NULL)
	{
		cerr << "请先建立二叉树！" << endl;
		return;
	}

	cout << "Please input key which inserted:";
	int num;
	cin >> num;
	if (cin.fail())
	{
		cerr << "请输入整数！" << endl;
		cin.clear();
		cin.ignore();
		return;
	}
	tree->renewRoot(tree->insert(num, tree->getRoot()));

	tree->showAll(tree->getRoot());
	cout << endl << endl;
	tree->showAll(tree->getRoot(), 0);
	cout << endl;
}

void search(OrderTree* tree)
{
	if (tree == NULL)
	{
		cerr << "请先建立二叉树！" << endl;
		return;
	}

	cout << "Please input key which searched:";
	int num;
	cin >> num;
	if (cin.fail())
	{
		cerr << "请输入整数！" << endl;
		cin.clear();
		cin.ignore();
		return;
	}
	tree->searh(num);
}