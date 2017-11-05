#include "heap.h"

void testHeap();
void testLeftistHeap();

int main()
{
	testLeftistHeap();
	getchar();
	getchar();
	return 0;
}

void testHeap()
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
	heap.popMin();
	heap.showHeap();
}

void testLeftistHeap()
{
	int size;
	cout << "请输入左式堆的大小！" << endl;
	cin >> size;
	while (cin.fail())
	{
		cerr << "请输入整数范围内的数字！" << endl;
		cin.clear();
		cin.ignore();
		cin >> size;
	}

	auto leftistHeap = LeftistHeap(size);
	leftistHeap.show();
}