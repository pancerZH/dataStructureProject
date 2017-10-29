#include "orderTree.h"

void buildTree(OrderTree*);
void insert(OrderTree*);
void search(OrderTree*);

int main()
{
	cout << "**\t\t二叉排序树\t\t**" << endl;
	cout << "==========================================" << endl;
	cout << "**\t\t1 --- 建立二叉排序树\t**" << endl;
	cout << "**\t\t2 --- 插入元素\t\t**" << endl;
	cout << "**\t\t3 --- 查询元素\t\t**" << endl;
	cout << "**\t\t4 --- 退出程序\t\t**" << endl;
	cout << "==========================================" << endl;

	OrderTree* tree = new OrderTree();
	if (tree == NULL)
	{
		cerr << "内存空间不足!" << endl;
		exit(1);
	}

	while (1)
	{
		int operation = 4;
		cout << endl << "Please select:";
		cin >> operation;

		switch (operation)
		{
		case 1:
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
					tree = new OrderTree();
					cout << "The old Tree has been deleted!" << endl;
					if (tree == NULL)
					{
						cerr << "内存空间不足！" << endl;
						exit(1);
					}
				}
				else
				{
					cout << "I will not delete the old Tree" << endl;
					break;
				}
			}
			buildTree(tree);
			break;
		case 2:
			insert(tree);
			break;
		case 3:
			search(tree);
			break;
		default:
			return 0;
		}
	}
}

void buildTree(OrderTree* tree)
{
	cout << "Please input key to create Bsort_Tree:" << endl;
	int num;
	cin >> num;
	while (num != 0)//0是输入结束的标记
	{
		tree->insert(num);
		cin >> num;
	}

	tree->showAll(tree->getRoot());
	cout << endl;
}

void insert(OrderTree* tree)
{
	cout << "Please input key which inserted:";
	int num;
	cin >> num;
	tree->insert(num);

	tree->showAll(tree->getRoot());
	cout << endl;
}

void search(OrderTree* tree)
{
	cout << "Please input key which searched:";
	int num;
	cin >> num;
	tree->searh(num);
}