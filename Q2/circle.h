#include<iostream>

using namespace std;

class Passenger {
public:
	Passenger(int id)
		:ID(id), next(NULL), front(NULL) {}
	int getID() { return ID; }
	bool linkNext(Passenger*);
	Passenger* next;
	Passenger* front;
private:
	int ID;
};

bool Passenger::linkNext(Passenger* nextPassenger)
{
	if (nextPassenger != NULL)
	{
		this->next = nextPassenger;
		nextPassenger->front = this;
		return true;
	}
	else
	{
		cout << "内存空间不足！" << endl;
		return false;
	}
}

class Circle {
public:
	Circle(int num, int start, int deathNum, int leftNum);
	~Circle();
	bool killUntilLeftNum();
	Passenger* killSomeone(Passenger* passenger, int killNum);
	void showAll();
private:
	Passenger* head;
	int totalNum;
	int deathNum;
	int leftNum;
};

Circle::Circle(int num, int start, int deathNum, int leftNum)
{
	head = new Passenger(1);//建立生死环
	if (head == NULL)
	{
		cout << "内存空间不足！" << endl;
		return;
	}
	Passenger* temp = head;
	int count = 2;
	while (count <= num)
	{
		temp->linkNext(new Passenger(count));
		if(temp->next != NULL)
			temp = temp->next;
		++count;
	}
	temp->linkNext(head);//构成双向循环链表

	while (start > 1)//找到起始旅客位置
	{
		head = head->next;
		--start;
	}

	this->totalNum = num;
	this->deathNum = deathNum;
	this->leftNum = leftNum;
}

Circle::~Circle()
{
	while (head != NULL)
	{
		Passenger* temp = head;
		head = head->next;
		delete temp;
		temp = NULL;
	}
}

bool Circle::killUntilLeftNum()
{
	Passenger* temp = head;
	int killNum = 0;
	while (leftNum != totalNum-killNum)
	{
		int count = 1;
		while (count != deathNum)//找到本次要被杀的人
		{
			temp = temp->next;
			++count;
		}
		++killNum;
		temp = killSomeone(temp,killNum);//杀掉此人
	}
	return true;
}

Passenger* Circle::killSomeone(Passenger* passenger, int killNum)
{
	Passenger* temp = passenger->next;
	passenger->front->next = temp;
	temp->front = passenger->front;

	if (passenger == head)//防止删除节点时丢失头结点
		head = temp;

	cout << "第" << killNum << "个死者位置是：\t" << passenger->getID() << endl;
	delete(passenger);
	passenger = NULL;

	return temp;//返回被杀的人下一个位置上的人
}

void Circle::showAll()
{
	Passenger* temp = head;
	cout << endl;
	cout << "最后剩下：\t" << leftNum << "人" << endl;
	cout << "剩余的生者位置为：\t" << temp->getID();
	temp = temp->next;

	while (temp != head)
	{
		cout << '\t' << temp->getID();
		temp = temp->next;
	}
	cout << endl;
}