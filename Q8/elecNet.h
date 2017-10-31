#include <iostream>
#include <string>

using namespace std;

class Node {
public:
	Node(const int num, const int money)
		:insideName(num) ,money(money), next(NULL) {}
	int insideName;//内部编号
	int money;
	Node* next;
};

class Feature {
public:
	Feature(const int weight, const int name)
		:known(false), weight(weight), whoChangeMe(name) {}
	bool update(const int, const int);
	bool known;//描述节点是否以权值最小的形式连接到生成树上
	int weight;//节点权值
	int whoChangeMe;//记录与它连接的那个点
};

bool Feature::update(const int newWeight, const int newChange)
{
	if (newWeight < weight)
	{
		weight = newWeight;
		whoChangeMe = newChange;
		return true;
	}
	else
		return false;
}

class Graph {
public:
	Graph(const int);
	~Graph();
	int storeName(const string);//将名称储存起来，返回编号
	bool storeAdja(const int, const int, const int);//将两个点储存在邻接表中
	bool initPrim(const int);//初始化最小生成树的各项相关参数
	int getMinFromFeatureList();
	bool buildPrimTree();//建立最小生成树
	void printPrimTree();//打印最小生成树
private:
	int numOfNode;//记录节点数量
	string* nameList;//对应节点名称和内部编号
	Node** adjaList;//储存图的邻接表
	Feature* featureList;//储存节点在生成树中的feature
};

Graph::Graph(const int size)
	:numOfNode(size)
{
	nameList = new string[numOfNode];
	adjaList = new Node*[numOfNode];
	featureList = (Feature*)malloc(sizeof(Feature)*numOfNode);
	if (nameList == NULL || adjaList == NULL||featureList == NULL)
	{
		cerr << "内存空间不足！" << endl;
		exit(1);
	}

	for (int i = 0;i < numOfNode;++i)//初始化两个表
	{
		nameList[i] = "null";
		adjaList[i] = NULL;
	}
}

Graph::~Graph()
{
	delete[] nameList;
	free(featureList);
	for (int i = 0;i < numOfNode;++i)
	{
		Node* temp = adjaList[i];
		while (temp != NULL)
		{
			Node* next = temp->next;
			delete temp;
			temp = next;
			next = NULL;
		}
	}
}

int Graph::storeName(const string name)
{
	for (int i = 0;i < numOfNode;++i)
	{
		if (nameList[i] == name)//如果已经在名称列表中
			return i;
		else if (nameList[i] == "null")//如果不在名称列表中
		{
			nameList[i] = name;
			return i;
		}
	}
	cerr << "输入错误！" << endl;
	exit(2);
}

/*将num2插入到num1名下的邻接表中。对于无向图，应交换num1和num2后再调用一次*/
bool Graph::storeAdja(const int num1, const int num2, const int money)
{
	Node* temp = adjaList[num1];
	if (temp == NULL)//该点下邻接表为空
	{
		adjaList[num1] = new Node(num2, money);
		if (adjaList[num1] == NULL)
		{
			cerr << "内存空间不足！" << endl;
			exit(1);
		}
		return true;
	}

	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new Node(num2, money);
	if (temp->next == NULL)
	{
		cerr << "内存空间不足！" << endl;
		exit(1);
	}
	return true;
}

bool Graph::initPrim(const int index)
{
	for (int i = 0;i < numOfNode;++i)//初始化特征表中的每项数值
	{
		if (adjaList[i] == NULL)//检查图中是否有孤立点
		{
			cout << "有孤立点，无法生成最小生成树！" << endl;
			return false;
		}
		featureList[i] = Feature(INT_MAX, -1);
	}
	featureList[index].weight = 0;//确定起始点
	return true;
}

int Graph::getMinFromFeatureList()
{
	int min = INT_MAX, name = -1;
	for (int i = 0;i < numOfNode;++i)
	{
		if (!featureList[i].known && featureList[i].weight < min)
		{
			min = featureList[i].weight;
			name = i;
		}
	}
	return name;
}

/*前置要求：无孤立点*/
bool Graph::buildPrimTree()
{
	bool allPointChecked = false;
	while (!allPointChecked)
	{
		int index = getMinFromFeatureList();//找到当前未达到最优状态的权值最小的点
		Node* temp = adjaList[index];//从邻接表中提取index的邻接点
		while (temp != NULL)
		{
			int name = temp->insideName;
			if(!featureList[name].known)
				featureList[name].update(temp->money, index);//更新权值
			temp = temp->next;
		}
		featureList[index].known = true;//index已被检测完毕，达到最优

		int i;
		for (i = 0;i < numOfNode;++i)//检测是否所有点都被检测完
			if (featureList[i].known == false)
				break;
		if (i == numOfNode)//所有点都被检测完毕
			allPointChecked = true;
	}
	return true;
}

void Graph::printPrimTree()
{
	for (int i = 0;i < numOfNode;++i)
	{
		for (int j = 0;j < numOfNode;++j)
		{
			if (featureList[j].whoChangeMe == i)
			{
				string name = nameList[j];
				string whoChangeMe = nameList[featureList[j].whoChangeMe];
				cout << whoChangeMe << "-(" << featureList[j].weight << ")->" << name << endl;
			}
		}
	}
}