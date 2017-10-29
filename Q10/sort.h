#include <iostream>
#include <ctime>

using namespace std;

class Sort {
	/*一律按照从小到大的顺序排序*/
public:
	Sort(const int);
	void copyNumGroup();//将生成的数组拷贝到操作数组中
	void swap(int&, int&);//交换提供的两个元素
	bool check();//检查排序是否正确
	void show();//打印排序后的数组
	void bubble();//冒泡排序
	void selection();//选择排序
	void insertion();//直接插入排序
	void shell();//希尔排序
private:
	int size;
	int* numGroup;
	int* copyGroup;
};

Sort::Sort(const int size)
	:size(size)
{
	numGroup = new int[size];
	copyGroup = new int[size];
	if (numGroup == NULL || copyGroup == NULL)
	{
		cerr << "内存空间不足！" << endl;
		exit(1);
	}

	for (int i = 0;i < size;++i)
		*(numGroup + i) = rand();
}

void Sort::copyNumGroup()
{
	for (int i = 0;i < size;++i)
		*(copyGroup + i) = *(numGroup + i);
}

void Sort::swap(int& i, int& j)
{
	int changeNum = i;
	i = j;
	j = changeNum;
}

bool Sort::check()
{
	for (int i = 0;i < size - 1;++i)
	{
		if (copyGroup[i] > copyGroup[i + 1])//发现未排好序的数字
		{
			cout << "排序失败！" << endl;
			return false;
		}
	}
	cout << "排序成功！" << endl;
	return true;
}

void Sort::show()
{
	for (int i = 0;i < size;++i)
		cout << copyGroup[i] << ' ';
	cout << endl;
}

void Sort::bubble()
{
	copyNumGroup();//将数据复制到操作数组中
	int total = 0;
	clock_t start, finish;
	
	start = clock();
	for (int i = 0;i < size - 1;++i)
	{
		for (int j = 0;j < size - 1 - i;++j)
		{
			if (copyGroup[j] > copyGroup[j + 1])
			{
				swap(copyGroup[j], copyGroup[j + 1]);
				++total;
			}
		}
	}
	finish = clock();

	cout << "冒泡排序所用时间：\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "冒泡排序交换次数：\t" << total << endl;
	check();
	//show();
}

void Sort::selection()
{
	copyNumGroup();//将数据复制到操作数组中
	int total = 0;
	clock_t start, finish;

	start = clock();
	for (int i = 0;i < size - 1;++i)
	{
		int min = copyGroup[size - 1];
		int position = size - 1;
		for (int j = i;j < size - 1;++j)
		{
			if (copyGroup[j] < min)
			{
				min = copyGroup[j];
				position = j;
				++total;
			}
		}

		swap(copyGroup[i], copyGroup[position]);
		++total;
	}
	finish = clock();

	cout << "选择排序所用时间：\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "选择排序交换次数：\t" << total << endl;
	check();
	//show();
}

void Sort::insertion()
{
	copyNumGroup();//将数据复制到操作数组中
	int total = 0;
	clock_t start, finish;

	start = clock();
	for (int i = 0;i < size;++i)
	{
		/*下面的每次循环都要检测第i个元素是否可以放在第j-1个元素之前*/
		/*由于前i-1个元素已经排好序，所以一旦发现无法继续向前移动，则停止循环*/
		for (int j = i;j > 0 && copyGroup[j - 1] > copyGroup[j];--j)
		{
			swap(copyGroup[j], copyGroup[j - 1]);//每次将第i个元素向前移动
			++total;
		}
	}
	finish = clock();

	cout << "直接插入排序所用时间：\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "直接插入排序交换次数：\t" << total << endl;
	check();
}

void Sort::shell()
{
	copyNumGroup();//将数据复制到操作数组中
	int total = 0;
	clock_t start, finish;

	int k, product = 1;
	for (k = 0;product * 2 - 1 <= size;++k)//找到Hibbard增量上界
		product *= 2;

	start = clock();
	for (int increment = product - 1;increment > 0;product /= 2, increment = product - 1)
	{
		/*希尔排序内部使用插入排序，并且可以保证前i个数字是increment-排序的*/
		for (int i = increment;i < size;++i)
		{
			for (int j = i;j >= increment;j -= increment)
			{
				if (copyGroup[j] < copyGroup[j - increment])
				{
					swap(copyGroup[j], copyGroup[j - increment]);
					++total;
				}
				else//已经排好序了
					break;
			}
		}
	}
	finish = clock();

	cout << "希尔排序所用时间：\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "希尔排序交换次数：\t" << total << endl;
	check();
}