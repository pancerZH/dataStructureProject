#include<iostream>

using namespace std;

class Chess {
public:
	Chess(const int size);
	~Chess();
	void showChess();
	bool checkPoint(const int x, const int y);
	int size;//���̳ߴ�
	int **field;
	int totalNum;//�ʺ�ڷ�
};

Chess::Chess(const int size)
	:size(size), totalNum(0)
{
	field = new int *[size];
	if (field == NULL)
	{
		cerr << "�ռ䲻�㣡" << endl;
		exit(1);
	}

	for (int i = 0;i < size;++i)
	{
		field[i] = new int[size];
		if (field[i] == NULL)
		{
			cerr << "�ռ䲻�㣡" << endl;
			exit(1);
		}
	}

	for (int i = 0;i < size;++i)
		for (int j = 0;j < size;++j)
			field[i][j] = 0;//0����ø����޻ʺ�1�����лʺ�
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
	for (int i = 0;i < size;++i)//���ͬһ�����Ƿ��лʺ�
		if (field[i][y] == 1)
			return false;
	
	for (int k = -(size - 1);k < size;++k)//������Խ������Ƿ��лʺ�
	{
		if (x + k < 0 || y + k < 0)//��δ�ִ����ϱ߽�
			continue;
		if (x + k > size - 1 || y + k > size - 1)//��Խ�����±߽�
			break;
		if (field[x + k][y + k] == 1)
			return false;
	}

	for (int k = -(size - 1);k < size;++k)//��鸱�Խ������Ƿ��лʺ�
	{
		if (x + k<0 || y - k>size - 1)//��δ�ִ����ϱ߽�
			continue;
		if (x + k > size - 1 || y - k < 0)//��Խ�����±߽�
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
	if (row == chess->size)//�ʺ��Ѿ�ȫ���������
	{
		chess->showChess();
		++(chess->totalNum);
		return;
	}

	for (int j = 0;j < chess->size;++j)
	{
		if (chess->checkPoint(row, j))
			chess->field[row][j] = 1;//���˸��ӷ��ϻʺ�
		else//���˸����޷���ֹ�ʺ��򿼲����ڵ���һ������
			continue;

		fillChess(row + 1);//���лʺ���úú󣬴�����һ��
		chess->field[row][j] = 0;//�˸��ӷ��ûʺ��ģ���ѽ������ع�����״̬����ʼ������һ������
	}
}