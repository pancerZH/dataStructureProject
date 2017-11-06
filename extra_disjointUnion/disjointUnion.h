#include <iostream>

using namespace std;

class Union {
	/*按高度求并*/
public:
	Union(const int);
	~Union();
	int find(const int);
	void setUnion(const int, const int);
	void showUnion();
private:
	int size;
	int* forest;
};

Union::Union(const int size)
	:size(size)
{
	forest = new int[size];
	if (forest == NULL)
	{
		cerr << "内存空间不足！" << endl;
		exit(1);
	}

	int i = size;
	while (i--)
		forest[i] = 0;
}

Union::~Union()
{
	delete[] forest;
	forest = NULL;
}

int Union::find(const int num)
{
	if (forest[num] <= 0)//此点是根节点
		return num;
	else
		return find(forest[num]);
}

void Union::setUnion(const int num1, const int num2)
{
	if (find(num1) == find(num2))
		cout << num1 << "和" << num2 << "已经处于同一集合中" << endl;
	else
	{
		if (forest[num1] < forest[num2])//num1比num2更高(负值)
			forest[num2] = num1;
		else if (forest[num1] > forest[num2])//num1比num2更矮
			forest[num1] = num2;
		else//两者深度相同
		{
			forest[num2] = num1;
			--forest[num1];//num1高度增加
		}
	}
}

void Union::showUnion()
{
	int i = 0;
	while (i < size)
	{
		cout << forest[i] << '\t';
		++i;
	}
	cout << endl;
}