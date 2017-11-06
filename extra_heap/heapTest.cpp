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
	heap.popMin();
	heap.showHeap();
}

void testLeftistHeap()
{
	int size;
	cout << "��������ʽ�ѵĴ�С��" << endl;
	cin >> size;
	while (cin.fail())
	{
		cerr << "������������Χ�ڵ����֣�" << endl;
		cin.clear();
		cin.ignore();
		cin >> size;
	}

	auto leftistHeap1 = LeftistHeap(size);
	leftistHeap1.show();
	/*cout << "===========================================" << endl;
	auto leftistHeap2 = LeftistHeap(size);
	leftistHeap2.show();
	cout << "===========================================" << endl;
	leftistHeap1.updateRoot(leftistHeap1.merge(leftistHeap1.getRoot(), leftistHeap2.getRoot()));
	leftistHeap1.show();*/
}