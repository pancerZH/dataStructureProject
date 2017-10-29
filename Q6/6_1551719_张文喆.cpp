#include "familyTree.h"

int main()
{
	cout << "**\t\t���׹���ϵͳ\t\t**" << endl;
	cout << "==========================================" << endl;
	cout << "**\t\t��ѡ��Ҫִ�еĲ���\t**" << endl;
	cout << "**\t\tA --- ���Ƽ�ͥ\t\t**" << endl;
	cout << "**\t\tB --- ��Ӽ�ͥ��Ա\t**" << endl;
	cout << "**\t\tC --- ��ɢ�ֲ���ͥ\t**" << endl;
	cout << "**\t\tD --- ���ļ�ͥ��Ա����\t**" << endl;
	cout << "**\t\tE --- �˳�����\t\t**" << endl;
	cout << "==========================================" << endl;

	cout << "���Ƚ���һ����ͥ��" << endl;
	cout << "���������ȵ�������";
	string ancestor;
	cin >> ancestor;
	auto familyTree = new Tree(ancestor);
	if (familyTree == NULL)
	{
		cerr << "�ռ䲻�㣡" << endl;
		exit(1);
	}
	cout << "�˼��׵������ǣ�" << ancestor << endl;

	while (1)
	{
		cout << endl << "��ѡ��Ҫִ�еĲ�����";
		char operation;
		cin >> operation;
		operation = toupper(operation);
		cin.clear();

		switch (operation)
		{
		case 'A':
			familyTree->addFamily();
			break;
		case 'B':
			familyTree->addOneSon();
			break;
		case 'C':
			familyTree->dismissFamily();
			break;
		case 'D':
			familyTree->changeName();
			break;
		default:
			return 0;
		}
	}
}