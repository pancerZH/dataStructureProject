#include "elecNet.h"

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
			while (num < 1)
			{
				cerr << "���������0СINT_MAX�Ķ��������" << endl;
				cin.clear();
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
		graph->storeName(name);
	}
}

void enterEdge(Graph* graph)
{
	int num1, num2, money;
	string name1, name2;
	cout << "�������������㼰�ߣ�";
	cin >> name1 >> name2 >> money;
	while (name1 != "?" && name2 != "?" && money > 0)
	{
		num1 = graph->storeName(name1);
		num2 = graph->storeName(name2);
		/*��Ϊ������ͼ�����������㶼Ҫ���ഢ��Է�*/
		graph->storeAdja(num1, num2, money);
		graph->storeAdja(num2, num1, money);

		cout << "�������������㼰�ߣ�";
		cin >> name1 >> name2 >> money;
	}
}

void buildTree(Graph* graph)
{
	string name;
	cout << "��������ʼ���㣺";
	cin >> name;
	int index = graph->storeName(name);
	graph->initPrim(index);
	graph->buildPrimTree();
	cout << "����Prim��С��������" << endl;
}