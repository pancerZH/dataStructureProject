#include "woodHeap.h"

int main()
{
	int size;
	cin >> size;
	while (size < 1)
	{
		cerr << "请输入大于0的数字N！" << endl;
		cin.clear();
		cin >> size;
	}

	int count = size, length;
	auto queue = new int[size + 1];
	while (count--)
	{
		cin >> length;
		if (length < 1)
		{
			cerr << "请输入大于0的木材长度！" << endl;
			cin.clear();
			delete queue;
			queue = new int[size + 1];
			count = size;
		}

		queue[size - count] = length;
	}

	auto woodHeap = new Heap(queue, size);
	woodHeap->findBestSolu();

	getchar();
	getchar();
	return 0;
}