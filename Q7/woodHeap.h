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
	int size;//������Ԫ�صĸ��������������ͷ0��
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
		if (child < size && queue[child + 1] < queue[child])//�ҵ��ýڵ��С�Ķ���
			++child;

		if (downElement > queue[child])
			queue[i] = queue[child];//��Ѩ����һ��
		else
			break;
	}
	queue[i] = downElement;//�����˵�Ԫ�������Ѩ
}

void Heap::percolateUp()
{
	int i;
	int upElement = queue[size];//�����һ��Ԫ�����ˣ��ʺ����������

	for (i = size;queue[i / 2] > upElement;i /= 2)
		queue[i] = queue[i / 2];//��Ѩ����һ��
	queue[i] = upElement;//������Ԫ�������Ѩ
}

int Heap::popMin()
{
	int min = queue[1];
	queue[1] = queue[size];//�����һ��Ԫ�ط��ڿ�ͷ
	--size;//��������
	percolateDown(1);//����
	return min;
}

void Heap::insert(const int sum)
{
	++size;//�����쳤
	queue[size] = sum;//���¼����Ԫ�ط��ڶ���ĩβ
	percolateUp();
}

void Heap::findBestSolu()
{
	while (size > 1)
	{
		int sum = popMin() + popMin();//��������С�Ļ��������������Ӷ�����ɾ��
		insert(sum);//��������֮�Ͳ������
		totalMoney += sum;
	}
	cout << totalMoney << endl;//��ʱsize=1�����ѵõ����ս��
}

void Heap::showHeap()
{
	for (int i = 1;i <= size;++i)
	{
		cout << queue[i] << '\t';
	}
	cout << endl;
}