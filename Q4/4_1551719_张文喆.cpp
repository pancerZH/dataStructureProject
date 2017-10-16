#include "queen.h"

int main()
{
	int size;
	cout << "现有NXN的棋盘，放入N个皇后，要求所有皇后不在同一行、列和斜线上！" << endl;
	cout << endl << "请输入皇后的个数：";
	cin >> size;
	cout << endl << "皇后摆法：" << endl << endl;

	auto chess = new Chess(size);
	auto queen = new Queen(chess);
	queen->fillChess(0);

	getchar();
	getchar();
	return 0;
}