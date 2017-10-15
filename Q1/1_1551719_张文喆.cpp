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
		cout << "�ڴ�ռ䲻�㣡" << endl;
		return 1;
	}
	cout << "�����뽨��������Ϣϵͳ!" << endl;
	cout << "�����뿼��������" << endl;
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
			cout << "�ڴ�ռ䲻�㣡" << endl;
			return 1;
		}
		database->insert(count, temp);
		++count;
		--numOfStu;
	}
	database->showAll();
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;

	while (1)
	{
		cout << "��ѡ����Ҫ���еĲ�����";
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
	cout << "��������Ҫ����Ŀ�����λ�ã�";
	int pos;
	cin >> pos;

	string num;
	string name;
	string sex;
	string age;
	string job;
	cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա������Լ��������" << endl;
	cin >> num >> name >> sex >> age >> job;

	auto stu = new Student(num, name, sex, age, job);
	if (stu == NULL)
	{
		cout << "�ڴ�ռ䲻�㣡" << endl;
		return false;
	}
	return database->insert(pos, stu);
}

bool deleteStu(Database* database)
{
	cout << "������Ҫɾ���Ŀ����Ŀ��ţ�" << endl;
	string num;
	cin >> num;
	return database->deleteStu(num);
}

bool find(Database* database)
{
	cout << "������Ҫ���ҵĿ����Ŀ��ţ�" << endl;
	string num;
	cin >> num;
	auto stu = database->find(num);
	if (stu == NULL)
	{
		cout << "���޴��ˣ�" << endl;
		return false;
	}
	cout << database->find(num)->getInfo() << endl;
	return true;
}

bool fix(Database* database)
{
	cout << "����������Ҫ�޸ĵĿ����Ŀ��ţ��������Ա������Լ��������" << endl;
	string num;
	string name;
	string sex;
	string age;
	string job;
	cin >> num >> name >> sex >> age >> job;

	return database->fix(num, name, sex, age, job);
}