#include <iostream>
#include <string>

using namespace std;

class Node {
public:
	Node(const int num, const int money)
		:insideName(num) ,money(money), next(NULL) {}
	int insideName;//�ڲ����
	int money;
	Node* next;
};

class Feature {
public:
	Feature(const int weight, const int name)
		:known(false), weight(weight), whoChangeMe(name) {}
	bool update(const int, const int);
	bool known;//�����ڵ��Ƿ���Ȩֵ��С����ʽ���ӵ���������
	int weight;//�ڵ�Ȩֵ
	int whoChangeMe;//��¼�������ӵ��Ǹ���
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
	bool storeName(const string);//�����ƴ�������
	int findName(const string);//���ڲ����ת��Ϊԭʼ����
	bool storeAdja(const int, const int, const int);//�������㴢�����ڽӱ���
	bool initPrim(const int);//��ʼ����С�������ĸ�����ز���
	int getMinFromFeatureList();
	bool buildPrimTree();//������С������
	void printPrimTree();//��ӡ��С������
private:
	int numOfNode;//��¼�ڵ�����
	string* nameList;//��Ӧ�ڵ����ƺ��ڲ����
	Node** adjaList;//����ͼ���ڽӱ�
	Feature* featureList;//����ڵ����������е�feature
};

Graph::Graph(const int size)
	:numOfNode(size)
{
	nameList = new string[numOfNode];
	adjaList = new Node*[numOfNode];
	featureList = (Feature*)malloc(sizeof(Feature)*numOfNode);
	if (nameList == NULL || adjaList == NULL||featureList == NULL)
	{
		cerr << "�ڴ�ռ䲻�㣡" << endl;
		exit(1);
	}

	for (int i = 0;i < numOfNode;++i)//��ʼ��������
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

bool Graph::storeName(const string name)
{
	for (int i = 0;i < numOfNode;++i)
	{
		if (nameList[i] == name)//����Ѿ��������б���
			return false;
		else if (nameList[i] == "null")//������������б���
		{
			nameList[i] = name;
			return true;
		}
	}
	cerr << "�������" << endl;//���������޷������б�
	exit(2);
}

int Graph::findName(const string name)
{
	for (int i = 0;i < numOfNode;++i)
		if (nameList[i] == name)//����ҵ�������
			return i;
	return -1;//δ�ҵ�����
}

/*��num2���뵽num1���µ��ڽӱ��С���������ͼ��Ӧ����num1��num2���ٵ���һ��*/
bool Graph::storeAdja(const int num1, const int num2, const int money)
{
	Node* temp = adjaList[num1];
	if (temp == NULL)//�õ����ڽӱ�Ϊ��
	{
		adjaList[num1] = new Node(num2, money);
		if (adjaList[num1] == NULL)
		{
			cerr << "�ڴ�ռ䲻�㣡" << endl;
			exit(1);
		}
		return true;
	}

	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new Node(num2, money);
	if (temp->next == NULL)
	{
		cerr << "�ڴ�ռ䲻�㣡" << endl;
		exit(1);
	}
	return true;
}

bool Graph::initPrim(const int index)
{
	for (int i = 0;i < numOfNode;++i)//��ʼ���������е�ÿ����ֵ
	{
		if (adjaList[i] == NULL)//���ͼ���Ƿ��й�����
		{
			cout << "�й����㣬�޷�������С��������" << endl;
			return false;
		}
		featureList[i] = Feature(INT_MAX, -1);
	}
	featureList[index].weight = 0;//ȷ����ʼ��
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

/*ǰ��Ҫ���޹�����*/
bool Graph::buildPrimTree()
{
	bool allPointChecked = false;
	int numOfChecked = 0;
	while (!allPointChecked)
	{
		int index = getMinFromFeatureList();//�ҵ���ǰδ�ﵽ����״̬��Ȩֵ��С�ĵ�
		if (index == -1)
		{
			cerr << "������ӵ����ıߣ�" << endl;
			return false;
		}

		Node* temp = adjaList[index];//���ڽӱ�����ȡindex���ڽӵ�
		while (temp != NULL)
		{
			int name = temp->insideName;
			if(!featureList[name].known)
				featureList[name].update(temp->money, index);//����Ȩֵ
			temp = temp->next;
		}
		featureList[index].known = true;//index�ѱ������ϣ��ﵽ����
		++numOfChecked;//�������ĵ����Ŀ��1

		if (numOfChecked == numOfNode)//���е㶼��������
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
				cout << whoChangeMe << "-(" << featureList[j].weight << ")->" << name << '\t';
			}
		}
	}
}