#include "orderTree.h"

bool checkIfThereIsATree(OrderTree*);
void buildTree(OrderTree*);
void buildTreeAVL(OrderTree*);
void insert(OrderTree*);
void insertAVL(OrderTree*);
void search(OrderTree*);

int main()
{
	cout << "**\t\t����������\t\t**" << endl;
	cout << "==========================================" << endl;
	cout << "**\t\t0 --- ����AVL��\t\t**" << endl;
	cout << "**\t\t1 --- ��������������\t**" << endl;
	cout << "**\t\t2 --- ����Ԫ��\t\t**" << endl;
	cout << "**\t\t3 --- ��ѯԪ��\t\t**" << endl;
	cout << "**\t\t4 --- �˳�����\t\t**" << endl;
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
					cerr << "�ڴ�ռ䲻��!" << endl;
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
					cerr << "�ڴ�ռ䲻��!" << endl;
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

	if (!tree->isEmpty)//����Ƿ��Ѿ�������һ����
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
	return false;//û�н�������
}

void buildTree(OrderTree* tree)
{
	cout << "Please input key to create Bsort_Tree:" << endl;
	int num;
	cin >> num;
	if (cin.fail())
	{
		cerr << "����ʧ�ܣ�������������" << endl;
		cin.clear();
		cin.ignore();
		return;
	}
	while (num != 0)//0����������ı��
	{
		tree->insert(num);
		cin >> num;
		if (cin.fail())
		{
			cerr << "����ʧ�ܣ�������������" << endl;
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
		cerr << "����ʧ�ܣ�������������" << endl;
		cin.clear();
		cin.ignore();
		return;
	}
	while (num != 0)//0����������ı��
	{
		tree->renewRoot(tree->insert(num, tree->getRoot()));
		cin >> num;
		if (cin.fail())
		{
			cerr << "����ʧ�ܣ�������������" << endl;
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
		cerr << "���Ƚ�����������" << endl;
		return;
	}

	cout << "Please input key which inserted:";
	int num;
	cin >> num;
	if (cin.fail())
	{
		cerr << "������������" << endl;
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
		cerr << "���Ƚ�����������" << endl;
		return;
	}

	cout << "Please input key which inserted:";
	int num;
	cin >> num;
	if (cin.fail())
	{
		cerr << "������������" << endl;
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
		cerr << "���Ƚ�����������" << endl;
		return;
	}

	cout << "Please input key which searched:";
	int num;
	cin >> num;
	if (cin.fail())
	{
		cerr << "������������" << endl;
		cin.clear();
		cin.ignore();
		return;
	}
	tree->searh(num);
}