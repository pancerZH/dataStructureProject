#include<iostream>

using namespace std;

class Chess {
public:
	Chess(const int size);
	~Chess();
	void showChess();
	bool checkPoint(const int x, const int y);
	int size;//棋盘尺寸
	int **field;
	int totalNum;//皇后摆法
};

Chess::Chess(const int size)
	:size(size), totalNum(0)
{
	field = new int *[size];
	if (field == NULL)
	{
		cerr << "空间不足！" << endl;
		exit(1);
	}

	for (int i = 0;i < size;++i)
	{
		field[i] = new int[size];
		if (field[i] == NULL)
		{
			cerr << "空间不足！" << endl;
			exit(1);
		}
	}

	for (int i = 0;i < size;++i)
		for (int j = 0;j < size;++j)
			field[i][j] = 0;//0代表该格子无皇后，1代表有皇后
}

Chess::~Chess()
{
	for (int i = 0;i < size;++i)
	{
		delete[] field[i];
		field[i] = NULL;
	}
}

void Chess::showChess()
{
	for (int i = 0;i < size;++i)
	{
		for (int j = 0;j < size;++j)
			cout << ((field[i][j]==1)?'X':'O') << ' ';
		cout << endl;
	}
	cout << endl;
}

bool Chess::checkPoint(const int x, const int y)
{
	for (int i = 0;i < size;++i)//检查同一列上是否有皇后
		if (field[i][y] == 1)
			return false;
	
	for (int k = -(size - 1);k < size;++k)//检查主对角线上是否有皇后
	{
		if (x + k < 0 || y + k < 0)//还未抵达左上边界
			continue;
		if (x + k > size - 1 || y + k > size - 1)//已越过右下边界
			break;
		if (field[x + k][y + k] == 1)
			return false;
	}

	for (int k = -(size - 1);k < size;++k)//检查副对角线上是否有皇后
	{
		if (x + k<0 || y - k>size - 1)//还未抵达右上边界
			continue;
		if (x + k > size - 1 || y - k < 0)//已越过左下边界
			break;
		if (field[x + k][y - k] == 1)
			return false;
	}

	return true;
}

class Queen {
public:
	Queen(Chess* chess)
		:chess(chess) {}
	void fillChess(const int row);
private:
	Chess* chess;
};

void Queen::fillChess(const int row)
{
	if (row == chess->size)//皇后已经全部放置完毕
	{
		chess->showChess();
		++(chess->totalNum);
		return;
	}

	for (int j = 0;j < chess->size;++j)
	{
		if (chess->checkPoint(row, j))
			chess->field[row][j] = 1;//将此格子放上皇后
		else//若此格子无法防止皇后，则考察相邻的下一个格子
			continue;

		fillChess(row + 1);//此行皇后放置好后，处理下一行
		chess->field[row][j] = 0;//此格子放置皇后的模拟已结束，回归无子状态，开始考察下一个格子
	}
}