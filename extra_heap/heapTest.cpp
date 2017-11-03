#include "heap.h"

int main()
{
	int size;
	cout << "请输入二叉堆的大小！" << endl;
	cin >> size;
	while (cin.fail())
	{
		cerr << "请输入整数范围内的数字！" << endl;
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