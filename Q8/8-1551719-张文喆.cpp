#include "elecNet.h"

void enterNode(int, Graph*);
void enterEdge(Graph*);
void buildTree(Graph*);

int main()
{
	cout << "==================================================" << endl;
	cout << "**\t\t电网造价模拟系统\t\t**" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\tA --- 创建电网顶点\t\t**" << endl;
	cout << "**\t\tB --- 添加电网的边\t\t**" << endl;
	cout << "**\t\tC --- 构造最小生成树\t\t**" << endl;
	cout << "**\t\tD --- 显示最小生成树\t\t**" << endl;
	cout << "**\t\tE --- 退出  程序\t\t**" << endl;
	cout << "==================================================" << endl;

	Graph* graph = NULL;

	while (1)
	{
		cout << endl << "请选择操作:";
		char operation;
		cin >> operation;

		switch (operation)
		{
		case 'A':
			cout << "请输入顶点的个数：";
			int num;
			cin >> num;
			while (num < 1)
			{
				cerr << "请输入大于0小INT_MAX的顶点个数！" << endl;
				cin.clear();
				cin >> num;
			}

			if (graph != NULL)
				delete graph;
			graph = new Graph(num);
			if (graph == NULL)
			{
				cerr << "内存空间不足！" << endl;
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
	cout << "请依此输入各顶点的名称：" << endl;
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
	cout << "请输入两个顶点及边：";
	cin >> name1 >> name2 >> money;
	while (name1 != "?" && name2 != "?" && money > 0)
	{
		num1 = graph->storeName(name1);
		num2 = graph->storeName(name2);
		/*因为是无向图，所以两个点都要互相储存对方*/
		graph->storeAdja(num1, num2, money);
		graph->storeAdja(num2, num1, money);

		cout << "请输入两个顶点及边：";
		cin >> name1 >> name2 >> money;
	}
}

void buildTree(Graph* graph)
{
	string name;
	cout << "请输入起始顶点：";
	cin >> name;
	int index = graph->storeName(name);
	graph->initPrim(index);
	graph->buildPrimTree();
	cout << "生成Prim最小生成树！" << endl;
}