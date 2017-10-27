#include "circle.h"

int main()
{
	int totalNum, startNum, deathNum,leftNum;
	cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ�˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ��" << endl;
	cout << endl << "������������Ϸ��������N��";
	cin >> totalNum;
	cout << "��������Ϸ��ʼ��λ��S��";
	cin >> startNum;
	startNum %= totalNum;
	cout << "��������������M��";
	cin >> deathNum;
	while (deathNum < 1 || deathNum > totalNum)
	{
		cout << "���������0С�ڵ���������N����������M��" << endl;
		cin >> deathNum;
	}
	cout << "������ʣ�����������K��";
	cin >> leftNum;
	while (leftNum < 0 || leftNum > totalNum)
	{
		cout << "��������ڵ���0С�ڵ���������N��ʣ����������K��" << endl;
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