#include "circle.h"

int main()
{
	int totalNum, startNum, deathNum,leftNum;
	cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ�˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ��" << endl;
	cout << endl << "������������Ϸ��������N��";
	cin >> totalNum;
	cout << "��������Ϸ��ʼ��λ��S��";
	cin >> startNum;
	cout << "��������������M��";
	cin >> deathNum;
	cout << "������ʣ�����������K��";
	cin >> leftNum;

	auto circle = new Circle(totalNum, startNum, deathNum, leftNum);
	circle->killUntilLeftNum();
	circle->showAll();

	getchar();
	getchar();
	return 0;
}