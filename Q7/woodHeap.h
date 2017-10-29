#include <iostream>

using namespace std;

class Heap {
public:
	Heap(int*, const int);
	void percolateDown(const int);
	void percolateUp();
	int popMin();
	void insert(const int);
	void findBestSolu();
	void showHeap();
private:
	int* queue;
	int size;//队列中元素的个数（不包含标记头0）
	int totalMoney;
};

Heap::Heap(int* queue, const int size)
	:queue(queue), size(size), totalMoney(0)
{
	for (int i = size / 2;i > 0;--i)
		percolateDown(i);
}

void Heap::percolateDown(const int index)
{
	int i, child = 1;
	int downElement = queue[index];

	for (i = index;i * 2 <= size;i = child)
	{
		child = i * 2;
		if (child < size && queue[child + 1] < queue[child])//找到该节点较小的儿子
			++child;

		if (downElement > queue[child])
			queue[i] = queue[child];//空穴下滤一层
		else
			break;
	}
	queue[i] = downElement;//将下滤的元素填入空穴
}

void Heap::percolateUp()
{
	int i;
	int upElement = queue[size];//将最后一个元素上滤，故函数无需参数

	for (i = size;queue[i / 2] > upElement;i /= 2)
		queue[i] = queue[i / 2];//空穴上滤一层
	queue[i] = upElement;//将上滤元素填入空穴
}

int Heap::popMin()
{
	int min = queue[1];
	queue[1] = queue[size];//将最后一个元素放在开头
	--size;//队列缩短
	percolateDown(1);//下滤
	return min;
}

void Heap::insert(const int sum)
{
	++size;//队列伸长
	queue[size] = sum;//将新加入的元素放在队列末尾
	percolateUp();
}

void Heap::findBestSolu()
{
	while (size > 1)
	{
		int sum = popMin() + popMin();//将两个最小的花销加起来，并从队列中删除
		insert(sum);//将两花销之和插入队列
		totalMoney += sum;
	}
	cout << totalMoney << endl;//此时size=1，即已得到最终结果
}

void Heap::showHeap()
{
	for (int i = 1;i <= size;++i)
	{
		cout << queue[i] << '\t';
	}
	cout << endl;
}