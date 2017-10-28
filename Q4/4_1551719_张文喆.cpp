#include "queen.h"

int main()
{
	int size;
	cout << "现有NXN的棋盘，放入N个皇后，要求所有皇后不在同一行、列和斜线上！" << endl;
	cout << endl << "请输入皇后的个数：";
	cin >> size;
	while (size <= 0)
	{
		cout << "请输入大于0的皇后个数！" << endl;
		cin.clear();
		cin >> size;
	}
	cout << endl << "皇后摆法：" << endl << endl;

	auto chess = new Chess(size);
	auto queen = new Queen(chess);
	if (chess == NULL || queen == NULL)
	{
		cerr << "空间不足！" << endl;
		exit(1);
	}
	queen->fillChess(0);
	cout << "共有" << chess->totalNum << "种解法！" << endl;

	getchar();
	getchar();
	return 0;
}