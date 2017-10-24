#include<iostream>

using namespace std;

class Field {
public:
	Field();
	~Field();
	bool canAccess(int x, int y);
	void showMap();
private:
	int **field;
	int row;
	int column;
};

Field::Field()
	:row(7), column(7)
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
			field[i][j] = 0;

	field[1][1] = field[2][1] = field[3][1] = field[3][2] = field[3][3]
		= field[4][3] = field[4][4] = field[4][5] = field[5][5] = 1;//1代表可以通行，0代表不可通行
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
			if (field[i][j] == 1)
				cout << 'x' << '\t';
			else
				cout << '#' << '\t';
		}
		cout << endl << endl;
	}
}

class Point {
public:
	Point(int x, int y) :positionX(x), positionY(y) 
	{
		up = down = left = right = true;
		next = front = NULL;
	}
	Point* linkNext(int x, int y);
	int positionX;
	int positionY;
	bool up, down, left, right;
	Point* next;
	Point* front;
};

Point* Point::linkNext(int x, int y)
{
	if (x > this->positionX)//位于自身下面
		this->down = false;
	if (x < this->positionX)//位于自身上面
		this->up = false;
	if (y > this->positionY)//位于自身右面
		this->right = false;
	if (y < this->positionY)//位于自身左面
		this->left = false;

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
	: endX(endX),endY(endY)
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
	void showAll();
private:
	Point* head;
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
		if (temp->right && field->canAccess(temp->positionX, temp->positionY + 1))//向右走
			temp = temp->linkNext(temp->positionX, temp->positionY + 1);
		else if (temp->down && field->canAccess(temp->positionX + 1, temp->positionY))//向下走
			temp = temp->linkNext(temp->positionX + 1, temp->positionY);
		else if (temp->left && field->canAccess(temp->positionX, temp->positionY - 1))//向左走
			temp = temp->linkNext(temp->positionX, temp->positionY - 1);
		else if (temp->up && field->canAccess(temp->positionX - 1, temp->positionY))//向上走
			temp = temp->linkNext(temp->positionX - 1, temp->positionY);
		else
		{
			cout << "没有通路！" << endl;
			return false;
		}

		if (temp == NULL)
		{
			cerr << "内存空间不足！" << endl;
			exit(1);
		}
	}
	return true;
}

void Knight::showAll()
{
	Point* temp = head;
	cout << "迷宫路径：" << endl << endl;
	while (temp->next != NULL)
	{
		cout << "(" << temp->positionX << "," << temp->positionY << ")" << "--->";
		temp = temp->next;
	}
	cout << "(" << temp->positionX << "," << temp->positionY << ")";
}