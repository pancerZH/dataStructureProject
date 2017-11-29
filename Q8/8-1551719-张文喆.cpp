#include "elecNet.h"

using namespace std;

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
			while (cin.fail() || num < 1)
			{
				cerr << "请输入大于0小INT_MAX的顶点个数！" << endl;
				cin.clear();
				cin.ignore();//防止缓冲区溢出
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
			if (graph == NULL)
			{
				cerr << "请先创建电网顶点！" << endl;
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
	cout << "请依次输入各顶点的名称：" << endl;
	while (size--)
	{
		string name;
		cin >> name;
		if (!graph->storeName(name))
		{
			cerr << "请勿输入重名顶点！" << endl;
			exit(3);
		}
	}
}

void enterEdge(Graph* graph)
{
	if (graph == NULL)
	{
		cerr << "请先创建电网顶点！" << endl;
		return;
	}

	int num1, num2, money;
	string name1, name2;
	while(1)
	{
		cout << "请输入两个顶点及边：";
		cin >> name1 >> name2 >> money;
		if (name1 == "?" || name2 == "?")
			break;
		num1 = graph->findName(name1);
		num2 = graph->findName(name2);
		if (num1 == -1 || num2 == -1)
		{
			cerr << "输入的顶点不存在！" << endl;
			cin.clear();
			cin.ignore();
			continue;//输入出错时，要求重新输入
		}
		if (cin.fail() || money < 0)
		{
			cerr << "请输入正确的大于等于0的造价！" << endl;
			cin.clear();
			cin.ignore();
			continue;//输入出错时，要求重新输入
		}

		/*因为是无向图，所以两个点都要互相储存对方*/
		graph->storeAdja(num1, num2, money);
		graph->storeAdja(num2, num1, money);
	}
}

void buildTree(Graph* graph)
{
	if (graph == NULL)
	{
		cerr << "请先创建电网顶点！" << endl;
		return;
	}

	string name;
	cout << "请输入起始顶点：";
	cin >> name;
	int index = graph->findName(name);
	if (index == -1)
	{
		cerr << "不存在此顶点！" << endl;
		return;
	}
	if (!graph->initPrim(index))
	{
		cout << "Prim最小生成树生成失败！" << endl;
		return;
	}
	if (graph->buildPrimTree())
		cout << "生成Prim最小生成树！" << endl;
	else
		cout << "Prim最小生成树生成失败！" << endl;
}