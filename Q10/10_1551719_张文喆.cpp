#include "sort.h"

int main()
{
	cout << "**\t\t�����㷨�Ƚ�\t\t**" << endl;
	cout << "==========================================" << endl;
	cout << "**\t\t1 --- ð������\t\t**" << endl;
	cout << "**\t\t2 --- ѡ������\t\t**" << endl;
	cout << "**\t\t3 --- ֱ�Ӳ�������\t**" << endl;
	cout << "**\t\t4 --- ϣ������\t\t**" << endl;
	cout << "**\t\t5 --- ��������\t\t**" << endl;
	cout << "**\t\t6 --- ������\t\t**" << endl;
	cout << "**\t\t7 --- �鲢����\t\t**" << endl;
	cout << "==========================================" << endl;

	cout << endl << "������Ҫ������������ĸ�����";
	int num;
	cin >> num;
	while (num < 1)
	{
		cerr << "���������0С��INT_MAX�������������" << endl;
		cin.clear();
		cin >> num;
	}
	auto sort = new Sort(num);
	if (sort == NULL)
	{
		cerr << "�ڴ�ռ䲻�㣡" << endl;
		exit(1);
	}

	while (1)
	{
		cout << endl << "��ѡ�������㷨��\t";
		int operation;
		cin >> operation;

		switch (operation)
		{
		case 1:
			sort->bubble();
			break;
		case 2:
			sort->selection();
			break;
		case 3:
			sort->insertion();
			break;
		case 4:
			sort->shell();
			break;
		case 5:
			sort->quick();
			break;
		case 6:
			sort->heap();
			break;
		case 7:
			sort->merge();
			break;
		default:
			return 0;
		}
	}
}