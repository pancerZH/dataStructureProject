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
	Node* son;//链表的头指针
	Node* brother;//链表元素指针，不一定为头
	bool isInFamilyTree;
private:
	string name;
};

bool Node::addSon(Node* newSon)
{
	if (son == NULL)//如果此节点还没有儿子，直接将新儿子置于其下
	{
		son = newSon;
		return true;
	}
	else//若有儿子，将新儿子置为旧儿子兄弟
	{
		if (son->addBrother(newSon))
			return true;
		else
			return false;//插入失败
	}
}

bool Node::addBrother(Node* brother)
{
	Node* temp = this;
	while (temp->brother != NULL)//找到brother链表的末尾
	{
		temp = temp->brother;
	}
	temp->brother = brother;
	return true;
}

class Tree {
public:
	Tree(string);//使用祖先的名字建立家谱
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
		cerr << "空间不足！" << endl;
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
	if (node == NULL)//已遍历到树的最深处
		return NULL;
	else
	{
		if (node->isInFamilyTree && node->getName() == name)//找到节点
			return node;
		else//未找到节点
		{
			Node* temp = node->brother;
			temp = find(name, temp);
			if (temp != NULL)//在node的兄弟中找到了节点
				return temp;
			else//node的兄弟中不包含要寻找的节点
				temp = node->son;

			temp = find(name, temp);
			if (temp != NULL)//在node的子孙中找到了节点
				return temp;
			else
				return NULL;
		}
	}
}

bool Tree::addFamily()
{
	string father;
	cout << "请输入要建立家庭的人的姓名：";
	cin >> father;

	Node* temp = find(father, ancestor);
	if (temp == NULL)
	{
		cerr << "不存在此人！" << endl;
		return false;
	}

	int numOfSon;
	cout << "请输入" << father << "的儿女人数：";
	cin >> numOfSon;
	while (cin.fail() || numOfSon < 0)
	{
		cerr << "请输入大于0的儿女人数！" << endl;
		cin.clear();
		cin.ignore();
		cin >> numOfSon;
	}

	string nameOfSon;
	cout << "请依次输入" << father << "的儿女的姓名：";
	while (numOfSon--)
	{
		cin >> nameOfSon;
		Node* newSon = new Node(nameOfSon);
		if (newSon == NULL)
		{
			cerr << "空间不足！" << endl;
			exit(1);
		}
		temp->addSon(newSon);//插入新的子女
	}

	showSons(temp);
	return true;
}

bool Tree::addOneSon()
{
	string father;
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	cin >> father;
	
	Node* temp = find(father, ancestor);
	if (temp == NULL)
	{
		cerr << "不存在此人！" << endl;
		return false;
	}

	string nameOfSon;
	cout << "请输入" << father << "新添加的儿子（或女儿）的姓名：";
	cin >> nameOfSon;
	Node* newSon = new Node(nameOfSon);
	if (newSon == NULL)
	{
		cerr << "空间不足！" << endl;
		exit(1);
	}
	temp->addSon(newSon);//插入新的子女

	showSons(temp);
	return true;
}

bool Tree::dismissFamily()
{
	string father;
	cout << "请输入要解散家庭的人的姓名：";
	cin >> father;

	Node* temp = find(father, ancestor);
	if (temp == NULL)
	{
		cerr << "不存在此人！" << endl;
		return false;
	}

	cout << "要解散家庭的人是：" << father << endl;
	showSons(temp);
	releaseNode(temp->son);
	temp->isInFamilyTree = false;//进行懒惰删除
	temp->son = NULL;

	/*为了防止删空家族树，规定祖先不可删除*/
	if (ancestor->isInFamilyTree == false)//家族树已空
		ancestor->isInFamilyTree = true;
	return true;
}

bool Tree::changeName()
{
	string oldName;
	cout << "请输入要更改姓名的人的目前的姓名：";
	cin >> oldName;

	Node* temp = find(oldName, ancestor);
	if (temp == NULL)
	{
		cerr << "不存在此人！" << endl;
		return false;
	}

	string newName;
	cout << "请输入更改后的姓名：";
	cin >> newName;
	temp->changeName(newName);//改名
	cout << oldName << "已更名为" << newName << endl;

	return true;
}

void Tree::showSons(Node* father)
{
	Node* temp = father->son;
	cout << father->getName() << "的第一代子孙是：";
	while (temp != NULL)
	{
		if(temp->isInFamilyTree)//如果该成员未被删除
			cout << temp->getName() << '\t';
		temp = temp->brother;
	}
	cout << endl;
}