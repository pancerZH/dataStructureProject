#include "circle.h"

int main()
{
	int totalNum, startNum, deathNum,leftNum;
	cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ�˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ��" << endl;
	cout << endl << "������������Ϸ��������N��";
	cin >> totalNum;
	while (totalNum < 1)
	{
		cout << "���������0С��INT_MAX����������" << endl;
		cin.clear();
		cin.ignore();
		cin >> totalNum;
	}

	cout << "��������Ϸ��ʼ��λ��S��";
	cin >> startNum;
	while (startNum < 1 || startNum > totalNum)
	{
		cout << "���������0С�ڵ����������Ŀ�ʼλ�ã�" << endl;
		cin.clear();
		cin.ignore();
		cin >> startNum;
	}

	cout << "��������������M��";
	cin >> deathNum;
	while (deathNum < 1 || deathNum > totalNum)
	{
		cout << "���������0С�ڵ���������N����������M��" << endl;
		cin.clear();
		cin.ignore();
		cin >> deathNum;
	}

	cout << "������ʣ�����������K��";
	cin >> leftNum;
	while (leftNum < 0 || leftNum > totalNum)
	{
		cout << "��������ڵ���0С�ڵ���������N��ʣ����������K��" << endl;
		cin.clear();
		cin.ignore();
		cin >> leftNum;
	}

	auto circle = new Circle(totalNum, startNum, deathNum, leftNum);
	if (circle == NULL)
	{
		cerr << "�ռ䲻�㣡" << endl;
		exit(1);
	}
	circle->killUntilLeftNum();
	circle->showAll();

	getchar();
	getchar();
	return 0;
}