#include <iostream>
#include <string>

using namespace std;

class Node {
public:
	Node(string name)
		:name(name), son(NULL), brother(NULL), isInFamilyTree(true) {}
	string getName() { return name; }
	void changeName(string newName) { name = newName; }
	bool addSon(Node*);
	bool addBrother(Node*);
	Node* son;//�����ͷָ��
	Node* brother;//����Ԫ��ָ�룬��һ��Ϊͷ
	bool isInFamilyTree;
private:
	string name;
};

bool Node::addSon(Node* newSon)
{
	if (son == NULL)//����˽ڵ㻹û�ж��ӣ�ֱ�ӽ��¶�����������
	{
		son = newSon;
		return true;
	}
	else//���ж��ӣ����¶�����Ϊ�ɶ����ֵ�
	{
		if (son->addBrother(newSon))
			return true;
		else
			return false;//����ʧ��
	}
}

bool Node::addBrother(Node* brother)
{
	Node* temp = this;
	while (temp->brother != NULL)//�ҵ�brother�����ĩβ
	{
		temp = temp->brother;
	}
	temp->brother = brother;
	return true;
}

class Tree {
public:
	Tree(string);//ʹ�����ȵ����ֽ�������
	~Tree();
	void releaseNode(Node*);
	Node* find(string, Node*);
	bool addFamily();
	bool addOneSon();
	bool dismissFamily();
	bool changeName();
	void showSons(Node*);
private:
	Node* ancestor;
};

Tree::Tree(string name)
{
	Node* temp = new Node(name);
	if (temp == NULL)
	{
		cerr << "�ռ䲻�㣡" << endl;
		exit(1);
	}
	else
		ancestor = temp;
}

Tree::~Tree()
{
	releaseNode(ancestor);
}

void Tree::releaseNode(Node* node)
{
	if (node == NULL)
		return;
	else
	{
		releaseNode(node->brother);
		releaseNode(node->son);
		delete node;
		node = NULL;
	}
}

Node* Tree::find(string name, Node* node)
{
	if (node == NULL)//�ѱ������������
		return NULL;
	else
	{
		if (node->isInFamilyTree && node->getName() == name)//�ҵ��ڵ�
			return node;
		else//δ�ҵ��ڵ�
		{
			Node* temp = node->brother;
			temp = find(name, temp);
			if (temp != NULL)//��node���ֵ����ҵ��˽ڵ�
				return temp;
			else//node���ֵ��в�����ҪѰ�ҵĽڵ�
				temp = node->son;

			temp = find(name, temp);
			if (temp != NULL)//��node���������ҵ��˽ڵ�
				return temp;
			else
				return NULL;
		}
	}
}

bool Tree::addFamily()
{
	string father;
	cout << "������Ҫ������ͥ���˵�������";
	cin >> father;

	Node* temp = find(father, ancestor);
	if (temp == NULL)
	{
		cerr << "�����ڴ��ˣ�" << endl;
		return false;
	}

	int numOfSon;
	cout << "������" << father << "�Ķ�Ů������";
	cin >> numOfSon;
	while (cin.fail() || numOfSon < 0)
	{
		cerr << "���������0�Ķ�Ů������" << endl;
		cin.clear();
		cin.ignore();
		cin >> numOfSon;
	}

	string nameOfSon;
	cout << "����������" << father << "�Ķ�Ů��������";
	while (numOfSon--)
	{
		cin >> nameOfSon;
		Node* newSon = new Node(nameOfSon);
		if (newSon == NULL)
		{
			cerr << "�ռ䲻�㣡" << endl;
			exit(1);
		}
		temp->addSon(newSon);//�����µ���Ů
	}

	showSons(temp);
	return true;
}

bool Tree::addOneSon()
{
	string father;
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	cin >> father;
	
	Node* temp = find(father, ancestor);
	if (temp == NULL)
	{
		cerr << "�����ڴ��ˣ�" << endl;
		return false;
	}

	string nameOfSon;
	cout << "������" << father << "����ӵĶ��ӣ���Ů������������";
	cin >> nameOfSon;
	Node* newSon = new Node(nameOfSon);
	if (newSon == NULL)
	{
		cerr << "�ռ䲻�㣡" << endl;
		exit(1);
	}
	temp->addSon(newSon);//�����µ���Ů

	showSons(temp);
	return true;
}

bool Tree::dismissFamily()
{
	string father;
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	cin >> father;

	Node* temp = find(father, ancestor);
	if (temp == NULL)
	{
		cerr << "�����ڴ��ˣ�" << endl;
		return false;
	}

	cout << "Ҫ��ɢ��ͥ�����ǣ�" << father << endl;
	showSons(temp);
	releaseNode(temp->son);
	temp->isInFamilyTree = false;//��������ɾ��
	temp->son = NULL;

	/*Ϊ�˷�ֹɾ�ռ��������涨���Ȳ���ɾ��*/
	if (ancestor->isInFamilyTree == false)//�������ѿ�
		ancestor->isInFamilyTree = true;
	return true;
}

bool Tree::changeName()
{
	string oldName;
	cout << "������Ҫ�����������˵�Ŀǰ��������";
	cin >> oldName;

	Node* temp = find(oldName, ancestor);
	if (temp == NULL)
	{
		cerr << "�����ڴ��ˣ�" << endl;
		return false;
	}

	string newName;
	cout << "��������ĺ��������";
	cin >> newName;
	temp->changeName(newName);//����
	cout << oldName << "�Ѹ���Ϊ" << newName << endl;

	return true;
}

void Tree::showSons(Node* father)
{
	Node* temp = father->son;
	cout << father->getName() << "�ĵ�һ�������ǣ�";
	while (temp != NULL)
	{
		if(temp->isInFamilyTree)//����ó�Աδ��ɾ��
			cout << temp->getName() << '\t';
		temp = temp->brother;
	}
	cout << endl;
}