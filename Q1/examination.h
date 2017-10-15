#include <string>
#include <iostream>

using namespace std;

class Student {
public:
	Student(const string, const string, const string, const string, const string);//��ʼ������
	string getInfo();//���ؿ�����Ϣ
	string getNum() { return num; }//���ؿ���
	Student* front;//ָ����һ��������ָ��
	Student* next;//ָ����һ��������ָ��
	void changeName(const string name) { this->name = name; }
	void changeSex(const string sex) { this->sex = sex; }
	void changeAge(const string age) { this->age = age; }
	void changeJob(const string job) { this->job = job; }
	
private:
	string num;
	string name;
	string sex;
	string age;
	string job;
};

Student::Student(const string num, const string name, const string sex, const string age, const string job)//��ʼ������
	: num(num), name(name), sex(sex), age(age), job(job), front(NULL), next(NULL) {}

string Student::getInfo()
{
	string info;
	info = num + '\t' + name + '\t' + sex + '\t' + age + '\t' + job;
	return info;
}


class Database {
public:
	Database();
	~Database();//������ݿ��е���������
	Student* getHead() { return head; }
	bool insert(const int pos, Student* contain);
	Student* find(const string num);
	bool deleteStu(const string num);
	bool fix(const string, const string, const string, const string, const string);
	void showAll();
	
private:
	Student* head;
	int numOfData;
};

Database::Database()
	: head(NULL), numOfData(0) {}

Database::~Database()
{
	Student* ptr = head;
	while (ptr != NULL)
	{
		Student* temp = ptr->next;
		delete(ptr);
		ptr = temp;
	}
	head = NULL;
}

bool Database::insert(const int pos, Student* contain)
{
	Student* temp = head;

	if (pos == 1 || head == NULL)//��������ͷ��
	{
		if (head != NULL)//���ݿⲻΪ�գ���ͷ��������
		{
			contain->next = head;
			head = contain;
		}
		else
			head = contain;
	}
	else if (pos <= numOfData)//���������ڲ�
	{
		Student* temp = head;
		int count = 1;
		while (count < pos)
		{
			++count;
			temp = temp->next;
		}
		contain->next = temp;
		contain->front = temp->front;
		temp->front->next = contain;
		temp->front = contain;
	}
	else//��������β��
	{
		Student* temp = head;
		int count = 1;
		while (count < numOfData)//�ҵ����һ������
		{
			++count;
			temp = temp->next;
		}
		temp->next = contain;
		contain->front = temp;
	}

	++numOfData;
	return true;
}

Student* Database::find(const string num)
{
	Student* temp = head;

	while (temp != NULL)
	{
		if (temp->getNum() == num)
			break;
		else
			temp = temp->next;
	}

	return temp;
}

bool Database::deleteStu(const string num)
{
	Student* temp = find(num);
	if (temp != NULL)//�ҵ�����
	{
		if (temp->front == NULL)//�������ͷ��
		{
			head = temp->next;
			if(temp->next != NULL)//����δ��ɾ��
				temp->next->front = NULL;
		}
		else if(temp->next == NULL)//�������β��
		{
			temp->front->next = NULL;
		}
		else
		{
			temp->front->next = temp->next;
			temp->next->front = temp->front;
		}

		delete(temp);
		temp = NULL;
		--numOfData;
		return true;//ɾ���ɹ�
	}
	else//δ�ҵ�����
		return false;
}

bool Database::fix(const string num, const string name, const string sex, const string age, const string job)
{
	Student* temp = find(num);

	if (temp != NULL)//�ҵ�����
	{
		temp->changeName(name);
		temp->changeSex(sex);
		temp->changeAge(age);
		temp->changeJob(job);
		return true;
	}
	else//δ�ҵ�����
		return false;
}

void Database::showAll()
{
	Student* temp = head;
	string info;
	cout << "����\t����\t�Ա�\t����\t�������" << endl;
	while (temp != NULL)
	{
		info = temp->getInfo();
		cout << info << endl;
		temp = temp->next;
	}
}