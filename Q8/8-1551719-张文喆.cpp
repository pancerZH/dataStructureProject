#include "elecNet.h"

using namespace std;

void enterNode(int, Graph*);
void enterEdge(Graph*);
void buildTree(Graph*);

int main()
{
	cout << "==================================================" << endl;
	cout << "**\t\t�������ģ��ϵͳ\t\t**" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\tA --- ������������\t\t**" << endl;
	cout << "**\t\tB --- ��ӵ����ı�\t\t**" << endl;
	cout << "**\t\tC --- ������С������\t\t**" << endl;
	cout << "**\t\tD --- ��ʾ��С������\t\t**" << endl;
	cout << "**\t\tE --- �˳�  ����\t\t**" << endl;
	cout << "==================================================" << endl;

	Graph* graph = NULL;

	while (1)
	{
		cout << endl << "��ѡ�����:";
		char operation;
		cin >> operation;

		switch (operation)
		{
		case 'A':
			cout << "�����붥��ĸ�����";
			int num;
			cin >> num;
			while (cin.fail() || num < 1)
			{
				cerr << "���������0СINT_MAX�Ķ��������" << endl;
				cin.clear();
				cin.ignore();//��ֹ���������
				cin >> num;
			}

			if (graph != NULL)
				delete graph;
			graph = new Graph(num);
			if (graph == NULL)
			{
				cerr << "�ڴ�ռ䲻�㣡" << endl;
				exit(1);
			}

			enterNode(num, graph);
			break;
		case 'B':
			enterEdge(graph);
			break;
		case 'C':
			buildTree(graph);
			break;
		case 'D':
			if (graph == NULL)
			{
				cerr << "���ȴ����������㣡" << endl;
				break;
			}
			graph->printPrimTree();
			break;
		default:
			return 0;
		}
	}
}

void enterNode(int size, Graph* graph)
{
	cout << "�������������������ƣ�" << endl;
	while (size--)
	{
		string name;
		cin >> name;
		if (!graph->storeName(name))
		{
			cerr << "���������������㣡" << endl;
			exit(3);
		}
	}
}

void enterEdge(Graph* graph)
{
	if (graph == NULL)
	{
		cerr << "���ȴ����������㣡" << endl;
		return;
	}

	int num1, num2, money;
	string name1, name2;
	while(1)
	{
		cout << "�������������㼰�ߣ�";
		cin >> name1 >> name2 >> money;
		if (name1 == "?" || name2 == "?")
			break;
		num1 = graph->findName(name1);
		num2 = graph->findName(name2);
		if (num1 == -1 || num2 == -1)
		{
			cerr << "����Ķ��㲻���ڣ�" << endl;
			cin.clear();
			cin.ignore();
			continue;//�������ʱ��Ҫ����������
		}
		if (cin.fail() || money < 0)
		{
			cerr << "��������ȷ�Ĵ��ڵ���0����ۣ�" << endl;
			cin.clear();
			cin.ignore();
			continue;//�������ʱ��Ҫ����������
		}

		/*��Ϊ������ͼ�����������㶼Ҫ���ഢ��Է�*/
		graph->storeAdja(num1, num2, money);
		graph->storeAdja(num2, num1, money);
	}
}

void buildTree(Graph* graph)
{
	if (graph == NULL)
	{
		cerr << "���ȴ����������㣡" << endl;
		return;
	}

	string name;
	cout << "��������ʼ���㣺";
	cin >> name;
	int index = graph->findName(name);
	if (index == -1)
	{
		cerr << "�����ڴ˶��㣡" << endl;
		return;
	}
	if (!graph->initPrim(index))
	{
		cout << "Prim��С����������ʧ�ܣ�" << endl;
		return;
	}
	if (graph->buildPrimTree())
		cout << "����Prim��С��������" << endl;
	else
		cout << "Prim��С����������ʧ�ܣ�" << endl;
}