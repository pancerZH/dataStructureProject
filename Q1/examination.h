#include <string>
#include <iostream>

using namespace std;

class Student {
public:
	Student(const string, const string, const string, const string, const string);//初始化函数
	string getInfo();//返回考生信息
	string getNum() { return num; }//返回考号
	Student* front;//指向上一个考生的指针
	Student* next;//指向下一个考生的指针
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

Student::Student(const string num, const string name, const string sex, const string age, const string job)//初始化函数
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
	~Database();//清空数据库中的所有数据
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

	if (pos == 1 || head == NULL)//插在链表头部
	{
		if (head != NULL)//数据库不为空，即头部有数据
		{
			contain->next = head;
			head = contain;
		}
		else
			head = contain;
	}
	else if (pos <= numOfData)//插在链表内部
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
	else//插在链表尾部
	{
		Student* temp = head;
		int count = 1;
		while (count < numOfData)//找到最后一个数据
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
	if (temp != NULL)//找到考生
	{
		if (temp->front == NULL)//是链表的头部
		{
			head = temp->next;
			if(temp->next != NULL)//链表未被删光
				temp->next->front = NULL;
		}
		else if(temp->next == NULL)//是链表的尾部
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
		return true;//删除成功
	}
	else//未找到考生
		return false;
}

bool Database::fix(const string num, const string name, const string sex, const string age, const string job)
{
	Student* temp = find(num);

	if (temp != NULL)//找到考生
	{
		temp->changeName(name);
		temp->changeSex(sex);
		temp->changeAge(age);
		temp->changeJob(job);
		return true;
	}
	else//未找到考生
		return false;
}

void Database::showAll()
{
	Student* temp = head;
	string info;
	cout << "考号\t姓名\t性别\t年龄\t报考类别" << endl;
	while (temp != NULL)
	{
		info = temp->getInfo();
		cout << info << endl;
		temp = temp->next;
	}
}