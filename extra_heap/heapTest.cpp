#include "heap.h"

int main()
{
	int size;
	cout << "���������ѵĴ�С��" << endl;
	cin >> size;
	while (cin.fail())
	{
		cerr << "������������Χ�ڵ����֣�" << endl;
		cin.clear();
		cin.ignore();
		cin >> size;
	}

	auto heap = Heap(size);
	heap.insert(10);
	heap.showHeap();
	getchar();
	getchar();
	return 0;
}