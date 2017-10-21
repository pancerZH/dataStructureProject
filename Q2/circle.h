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
		cout << "�ڴ�ռ䲻�㣡" << endl;
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
	head = new Passenger(1);//����������
	if (head == NULL)
	{
		cout << "�ڴ�ռ䲻�㣡" << endl;
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
	temp->linkNext(head);//����˫��ѭ������

	while (start > 1)//�ҵ���ʼ�ÿ�λ��
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
		while (count != deathNum)//�ҵ�����Ҫ��ɱ����
		{
			temp = temp->next;
			++count;
		}
		++killNum;
		temp = killSomeone(temp,killNum);//ɱ������
	}
	return true;
}

Passenger* Circle::killSomeone(Passenger* passenger, int killNum)
{
	Passenger* temp = passenger->next;
	passenger->front->next = temp;
	temp->front = passenger->front;

	if (passenger == head)//��ֹɾ���ڵ�ʱ��ʧͷ���
		head = temp;

	cout << "��" << killNum << "������λ���ǣ�\t" << passenger->getID() << endl;
	delete(passenger);
	passenger = NULL;

	return temp;//���ر�ɱ������һ��λ���ϵ���
}

void Circle::showAll()
{
	Passenger* temp = head;
	cout << endl;
	cout << "���ʣ�£�\t" << leftNum << "��" << endl;
	cout << "ʣ�������λ��Ϊ��\t" << temp->getID();
	temp = temp->next;

	while (temp != head)
	{
		cout << '\t' << temp->getID();
		temp = temp->next;
	}
	cout << endl;
}