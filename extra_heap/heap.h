#include <iostream>

using namespace std;

class Heap {
public:
	Heap(const int);//�����齫��1��ʼ��¼����
	~Heap();
	bool extendSpace();//ʵ�ֱ�������
	void swap(int&, int&);
	bool insert(const int);
	int popMin();
	void percolateUp(const int);//����
	void percolateDown(const int);//����
	void showHeap();
	void showNum(const int, const int);
private:
	int size;
	int length;
	int* head;
};

Heap::Heap(const int size)//Ҫ��size����0
	:size(size), length(1)
{
	head = new int[size + 1];
	if (head == NULL)
	{
		cerr << "�ڴ�ռ䲻�㣡" << endl;
		exit(1);
	}
	head[0] = INT_MIN;//ͷ���Ϊ���

	cout << "������������֣�" << endl;
	int i = size, num;
	while (i--)
	{
		cin >> num;
		while (cin.fail())
		{
			cerr << "������������Χ�ڵ����֣�" << endl;
			cin.clear();
			cin.ignore();
			cin >> num;
		}
		head[length] = num;
		++length;
	}

	/*��������ת��Ϊ�����*/
	for (int i = size / 2;i > 0;--i)
		percolateDown(i);
}

Heap::~Heap()
{
	delete[] head;
	head = NULL;
}

bool Heap::extendSpace()
{
	size *= 2;
	int* temp = new int[size + 1];
	if (temp == NULL)
	{
		cerr << "�ڴ�ռ䲻�㣡" << endl;
		exit(1);
	}

	for (int i = 1;i < length;++i)
		temp[i] = head[i];
	
	delete[] head;
	head = temp;
	return true;
}

void Heap::swap(int& num1, int& num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}

bool Heap::insert(const int num)
{
	if (length == size + 1)//��װ������
		extendSpace();

	head[length] = num;
	percolateUp(length);
	++length;
	return true;
}

int Heap::popMin()
{
	if (length <= 1)
	{
		cerr << "�������û��Ԫ�أ�" << endl;
		return INT_MIN;
	}

	int min = head[1];
	head[1] = head[length - 1];
	--length;
	percolateDown(1);

	return min;
}

void Heap::percolateUp(const int index)
{
	for (int i = index;head[i] < head[i / 2];i /= 2)
		swap(head[i], head[i / 2]);
}

void Heap::percolateDown(const int index)
{
	for (int i = index, child = 2 * index;child < length;i = child)
	{
		/*�ҵ��������ӣ�����У��н�С���Ǹ����ڱȽ�*/
		if (child + 1 < length && head[child + 1] < head[child])
			++child;
		/*�������С�ڸ��ף���������ˣ������������ѭ��*/
		if (head[child] < head[i])
			swap(head[child], head[i]);
		else
			break;
	}
}

void Heap::showHeap()
{
	showNum(1, 0);
}

void Heap::showNum(const int index, const int depth)
{
	if (index >= length)
	{
		int i = depth;
		while (i--)
			cout << '\t';
		cout << "��" << endl;
		return;
	}

	showNum(index * 2, depth + 1);
	int i = depth;
	while (i--)
		cout << '\t';
	cout << head[index] << endl;
	showNum(index * 2 + 1, depth + 1);
}