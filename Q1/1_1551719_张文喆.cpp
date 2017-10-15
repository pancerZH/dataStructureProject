#include "examination.h"

using namespace std;

bool insert(Database* database);
bool deleteStu(Database* database);
bool find(Database* database);
bool fix(Database* database);

int main()
{
	auto database = new Database();
	if (database == NULL)
	{
		cout << "内存空间不足！" << endl;
		return 1;
	}
	cout << "首先请建立考生信息系统!" << endl;
	cout << "请输入考生人数：" << endl;
	int numOfStu;
	cin >> numOfStu;
	
	int count = 1;
	while (numOfStu)
	{
		string num;
		string name;
		string sex;
		string age;
		string job;
		cin >> num >> name >> sex >> age >> job;

		auto temp = new Student(num, name, sex, age, job);
		if (temp == NULL)
		{
			cout << "内存空间不足！" << endl;
			return 1;
		}
		database->insert(count, temp);
		++count;
		--numOfStu;
	}
	database->showAll();
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;

	while (1)
	{
		cout << "请选择您要进行的操作：";
		char ch;
		cin >> ch;

		switch (ch)
		{
		case '1':
			insert(database);
			database->showAll();
			break;
		case '2':
			deleteStu(database);
			database->showAll();
			break;
		case '3':
			find(database);
			break;
		case '4':
			fix(database);
			database->showAll();
			break;
		case '5':
			database->showAll();
		default:
			return 0;
		}
	}

	return 0;
}

bool insert(Database* database)
{
	cout << "请输入你要插入的考生的位置：";
	int pos;
	cin >> pos;

	string num;
	string name;
	string sex;
	string age;
	string job;
	cout << "请依此输入要插入的考生的考号，姓名，性别，年龄以及报考类别！" << endl;
	cin >> num >> name >> sex >> age >> job;

	auto stu = new Student(num, name, sex, age, job);
	if (stu == NULL)
	{
		cout << "内存空间不足！" << endl;
		return false;
	}
	return database->insert(pos, stu);
}

bool deleteStu(Database* database)
{
	cout << "请输入要删除的考生的考号！" << endl;
	string num;
	cin >> num;
	return database->deleteStu(num);
}

bool find(Database* database)
{
	cout << "请输入要查找的考生的考号！" << endl;
	string num;
	cin >> num;
	auto stu = database->find(num);
	if (stu == NULL)
	{
		cout << "查无此人！" << endl;
		return false;
	}
	cout << database->find(num)->getInfo() << endl;
	return true;
}

bool fix(Database* database)
{
	cout << "请依此输入要修改的考生的考号，姓名，性别，年龄以及报考类别！" << endl;
	string num;
	string name;
	string sex;
	string age;
	string job;
	cin >> num >> name >> sex >> age >> job;

	return database->fix(num, name, sex, age, job);
}