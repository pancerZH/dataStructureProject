#include<iostream>

#define BLOCK 0
#define SPACE 1
#define TESTED 2
#define SOLUTION 3

using namespace std;

class Field {
public:
	Field();
	~Field();
	bool canAccess(int x, int y);
	void showMap();
	int **field;
	bool isAccess;
private:
	int row;
	int column;
};

Field::Field()
	:row(7), column(7), isAccess(true)
{
	field = new int *[row];
	if (field == NULL)
	{
		cerr << "内存不足！" << endl;
		exit(1);
	}

	for (int i = 0; i < row; ++i)
	{
		field[i] = new int[column];
		if (field[i] == NULL)
		{
			cerr << "内存不足！" << endl;
			exit(1);
		}
	}

	for (int i = 0; i < row; ++i)
		for (int j = 0; j < column; ++j)
			field[i][j] = BLOCK;

	field[1][1] = field[2][1] = field[3][1] = field[3][2] = field[3][3] = field[2][5]
		= field[4][1] = field[5][1] = field[1][3] = field[2][3] = field[5][3] = field[1][4]
		= field[1][5] = field[4][3] = field[4][4] = field[3][5] = field[4][5] = field[5][5] = SPACE;
}

Field::~Field()
{
	for (int i = 0; i < row; ++i)
	{
		delete[] field[i];
		field[i] = NULL;
	}
}

bool Field::canAccess(int x, int y)
{
	if (x > row-1 || y > column-1 || x < 0 || y < 0)//越界
		return false;
	if (field[x][y] == 1)
		return true;
	else
		return false;
}

void Field::showMap()
{
	cout << "迷宫地图：" << endl << endl;
	cout << "\t" << "0列\t" << "1列\t" << "2列\t" << "3列\t" << "4列\t" << "5列\t" << "6列\t" << endl;
	for (int i = 0; i < row; ++i)
	{
		cout << i << "行\t";
		for (int j = 0; j < column; ++j)
		{
			if (field[i][j] == SOLUTION)
				cout << 'x' << '\t';
			else if (field[i][j] == BLOCK)
				cout << '#' << '\t';
			else
				cout << '0' << '\t';
		}
		cout << endl << endl;
	}
}

class Point {
public:
	Point(int x, int y) :positionX(x), positionY(y) 
	{
		next = front = NULL;
	}
	Point* linkNext(int x, int y);
	int positionX;
	int positionY;
	Point* next;
	Point* front;
};

Point* Point::linkNext(int x, int y)
{
	if (this->next != NULL)//删掉原有的节点
		delete(this->next);

	Point* temp = new Point(x, y);
	if (temp == NULL)//内存空间不足
	{
		cerr << "内存不足！" << endl;
		exit(1);
	}

	temp->front = this;
	this->next = temp;
	return temp;
}

class Knight {
public:
	Knight(int startX, int startY, int endX, int endY)
		: canReachEnd(true), endX(endX), endY(endY)
	{
		head = new Point(startX, startY);
		if (head == NULL)
		{
			cerr << "内存不足！" << endl;
			exit(1);
		}
	}
	~Knight();
	bool findWay(Field* field);
	void drawSolutionOnMap(Field* field);
	void showAll();
private:
	Point* head;
	bool canReachEnd;
	int endX;
	int endY;
};

Knight::~Knight()
{
	while (head != NULL)
	{
		Point* temp = head;
		head = head->next;
		delete temp;
		temp = NULL;
	}
}

bool Knight::findWay(Field* field)
{
	Point* temp = head;
	while (temp->positionX != endX || temp->positionY != endY)
	{
		field->field[temp->positionX][temp->positionY] = TESTED;//防止走回头路，使走过的路不可再走
		if (field->canAccess(temp->positionX - 1, temp->positionY))//向上走
			temp = temp->linkNext(temp->positionX - 1, temp->positionY);
		else if (field->canAccess(temp->positionX, temp->positionY - 1))//向左走
			temp = temp->linkNext(temp->positionX, temp->positionY - 1);
		else if (field->canAccess(temp->positionX, temp->positionY + 1))//向右走
			temp = temp->linkNext(temp->positionX, temp->positionY + 1);
		else if (field->canAccess(temp->positionX + 1, temp->positionY))//向下走
			temp = temp->linkNext(temp->positionX + 1, temp->positionY);
		else//无路可走，即没有通路
		{
			temp = temp->front;//回到链表中上一个节点处

			if (temp == NULL)//链表中已无可选择的路径，即无路可走
			{
				field->isAccess = false;//宣告迷宫无通路
				canReachEnd = false;//宣告骑士无法走出迷宫
				return false;
			}
		}

		if (temp == NULL)
		{
			cerr << "内存空间不足！" << endl;
			exit(1);
		}
	}
	return true;
}

void Knight::drawSolutionOnMap(Field* field)
{
	Point* temp = head;
	while (temp != NULL)
	{
		if(canReachEnd)
			field->field[temp->positionX][temp->positionY] = SOLUTION;
		else
			field->field[temp->positionX][temp->positionY] = SPACE;

		temp = temp->next;
	}
}

void Knight::showAll()
{
	if (!canReachEnd)//没有通路，不展示路径
	{
		cout << "没有通路！" << endl;
		return;
	}

	Point* temp = head;
	cout << "迷宫路径：" << endl << endl;
	while (temp->next != NULL)
	{
		cout << "(" << temp->positionX << "," << temp->positionY << ")" << "--->";
		temp = temp->next;
	}
	cout << "(" << temp->positionX << "," << temp->positionY << ")";
}