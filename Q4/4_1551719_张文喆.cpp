#include "queen.h"

int main()
{
	int size;
	cout << "����NXN�����̣�����N���ʺ�Ҫ�����лʺ���ͬһ�С��к�б���ϣ�" << endl;
	cout << endl << "������ʺ�ĸ�����";
	cin >> size;
	while (size <= 0)
	{
		cout << "���������0�Ļʺ������" << endl;
		cin.clear();
		cin >> size;
	}
	cout << endl << "�ʺ�ڷ���" << endl << endl;

	auto chess = new Chess(size);
	auto queen = new Queen(chess);
	if (chess == NULL || queen == NULL)
	{
		cerr << "�ռ䲻�㣡" << endl;
		exit(1);
	}
	queen->fillChess(0);
	cout << "����" << chess->totalNum << "�ֽⷨ��" << endl;

	getchar();
	getchar();
	return 0;
}