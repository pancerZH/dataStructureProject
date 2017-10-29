#include "woodHeap.h"

int main()
{
	int size;
	cin >> size;
	while (size < 1)
	{
		cerr << "���������0������N��" << endl;
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
			cerr << "���������0��ľ�ĳ��ȣ�" << endl;
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