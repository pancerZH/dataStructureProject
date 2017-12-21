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
	void quick();//快速排序
	void quickSort(const int, const int);//快速排序的子函数，用于递归
	void heap();//堆排序
	void percDown(const int, const int);//堆排序的子函数，用于空穴下滤
	void merge();//归并排序
	void divideMerge(int*, const int, const int);//归并排序的子函数，用于划分数组
	void mergeTwoPart(int*, int, int, int);//归并排序的子函数，用于合并两个已排序的表
	void bucket();//桶排序
	void radix();//基数排序
	int maxBit();//基数排序的辅助函数，获取数据的最高位数
private:
	int size;
	int* numGroup;
	int* copyGroup;
	int total;//排序时的交换计数
};

Sort::Sort(const int size)
	:size(size), total(0)
{
	numGroup = new int[size];
	copyGroup = new int[size];
	if (numGroup == NULL || copyGroup == NULL)
	{
		cerr << "内存空间不足！" << endl;
		exit(1);
	}

	srand(int(time));
	for (int i = 0;i < size;++i)
		/*保证生成的随机数大小范围为0~size-1*/
		*(numGroup + i) = rand() % size;
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
	this->total = 0;//交换计数归0
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
	this->total = 0;//交换计数归0
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
	this->total = 0;//交换计数归0
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
	this->total = 0;//交换计数归0
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

void Sort::quick()
{
	copyNumGroup();//将数据复制到操作数组中
	this->total = 0;//交换计数归0
	clock_t start, finish;

	start = clock();
	quickSort(0, size - 1);
	finish = clock();

	cout << "快速排序所用时间：\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "快速排序交换次数：\t" << total << endl;
	check();
}

void Sort::quickSort(const int left, const int right)
{
	int i = left, j = right;//分别指向数组的头尾
	if (right - left <= 20)//在数据较少时换用直接插入排序
	{
		for (int i = left;i <= right;++i)
		{
			/*下面的每次循环都要检测第i个元素是否可以放在第j-1个元素之前*/
			/*由于前i-1个元素已经排好序，所以一旦发现无法继续向前移动，则停止循环*/
			for (int j = i;j > 0 && copyGroup[j - 1] > copyGroup[j];--j)
			{
				swap(copyGroup[j], copyGroup[j - 1]);//每次将第i个元素向前移动
				++total;
			}
		}
		return;
	}

	int index = left + (rand() % (right - left + 1));
	int key = copyGroup[index];//找到基准元
	swap(copyGroup[index], copyGroup[right]);//将基准元割离出待排序部分
	--j;
	while (i <= j)
	{
		while (key < copyGroup[j])
			--j;//找到右侧第一个小于基准元的数
		while (key > copyGroup[i])
			++i;//找到左侧第一个大于基准元的数
		if (i < j)//如果两数未交错，则交换它们的值
		{
			swap(copyGroup[i], copyGroup[j]);
			++total;
			++i;
			--j;
		}
		else//若交错，则退出循环
			break;
	}
	swap(copyGroup[i], copyGroup[right]);//基准元归位
	++total;

	quickSort(left, i - 1);//继续处理左半部分
	quickSort(i + 1, right);//继续处理右半部分
}

void Sort::heap()
{
	copyNumGroup();//将数据复制到操作数组中
	this->total = 0;//交换计数归0
	clock_t start, finish;

	start = clock();
	for (int i = size / 2;i >= 0;--i)//建堆,最大的元素位于根部
		percDown(i, size);
	for (int i = size - 1;i > 0;--i)
	{
		/*将堆中最大元素排在排序区头部，排序区整体上为由小到大*/
		swap(copyGroup[i], copyGroup[0]);
		++total;
		percDown(0, i);
	}
	finish = clock();

	cout << "堆排序所用时间：\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "堆排序交换次数：\t" << total << endl;
	check();
}

void Sort::percDown(const int downIndex, const int endIndex)
{
	int childIndex;//它将指向两个儿子中较大的那一个
	for (int i = downIndex;2 * i + 1 < endIndex;i = childIndex)
	{
		childIndex = 2 * i + 1;//现在指示的是左儿子的坐标
		/*存在的前提下，若右儿子大于左儿子，则将childIndex改为左儿子坐标*/
		if (childIndex != endIndex - 1 && copyGroup[childIndex] < copyGroup[childIndex + 1])
			++childIndex;
		if (copyGroup[i] < copyGroup[childIndex])
		{
			swap(copyGroup[i], copyGroup[childIndex]);//元素下滤
			++total;
		}
		else//下滤的元素找到了合适的位置；恢复了堆序性
			break;
	}
}

void Sort::merge()
{
	copyNumGroup();//将数据复制到操作数组中
	this->total = 0;//比较计数归0
	clock_t start, finish;

	start = clock();
	int* tempArr = new int[size];
	if (tempArr == NULL)
	{
		cerr << "内存空间不足！" << endl;
		exit(1);
	}

	divideMerge(tempArr, 0, size - 1);
	delete[] tempArr;
	tempArr = NULL;
	finish = clock();

	cout << "归并排序所用时间：\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "归并排序比较次数：\t" << total << endl;
	check();
}

void Sort::divideMerge(int* tempArr, const int left, const int right)
{
	int center;
	if (left < right)//传入的部分可以继续划分
	{
		center = (left + right) / 2;
		/*划分为left~center部分，center成为新的right*/
		divideMerge(tempArr, left, center);
		/*划分为center+1~right部分，center+1成为新的left*/
		divideMerge(tempArr, center + 1, right);
		/*将两部分合并*/
		mergeTwoPart(tempArr, left, center + 1, right);
	}
}

void Sort::mergeTwoPart(int* tempArr, int left, int right, int rightEnd)
{
	int leftEnd = right - 1;//左边部分的结尾位于right前一位
	int tempPos = left;//临时数组的索引位置
	int numOfElem = rightEnd - left + 1;//两个数组中元素的总数

	while (left <= leftEnd && right <= rightEnd)//任意一部分未被检测完时
	{
		++total;
		if (copyGroup[left] < copyGroup[right])//找出两部分数组中对应位置上较小的
			tempArr[tempPos++] = copyGroup[left++];//将左边数组上的数字放入临时数组
		else
			tempArr[tempPos++] = copyGroup[right++];
	}

	/*下面两个while只可能执行一个，目的是将未检测完的那个数组插入临时数组*/
	while (left <= leftEnd)//将左边数组剩余部分顺序插入临时数组
		tempArr[tempPos++] = copyGroup[left++];
	while (right <= rightEnd)//将右边数组剩余部分顺序插入临时数组
		tempArr[tempPos++] = copyGroup[right++];

	/*将排序好的元素从临时数组中拷贝回操作数组*/
	for (int i = 0;i < numOfElem;++i, --rightEnd)
		copyGroup[rightEnd] = tempArr[rightEnd];
}

void Sort::bucket()
{
	copyNumGroup();//将数据复制到操作数组中
	this->total = 0;//比较计数归0
	clock_t start, finish;

	start = clock();
	int* bucket = new int[size];//开辟桶空间
	if (bucket == NULL)
	{
		cerr << "内存空间不足！" << endl;
		exit(1);
	}
	/*将桶内元素赋值为0*/
	for (int i = 0;i < size;++i)
		bucket[i] = 0;

	/*将待排序元素放入桶中*/
	for (int i = 0;i < size;++i)
		++bucket[copyGroup[i]];

	/*将桶中元素按顺序放回操作数组*/
	int pos = 0;
	for (int i = 0;i < size;++i)
		for (int j = bucket[i];j > 0;--j)
			copyGroup[pos++] = i;
	delete[] bucket;
	finish = clock();

	cout << "桶排序所用时间：\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "桶排序比较次数：\t" << total << endl;
	check();
}

void Sort::radix()//LSD方法实现
{
	copyNumGroup();//将数据复制到操作数组中
	this->total = 0;//比较计数归0
	clock_t start, finish;

	start = clock();
	int max = maxBit();
	int* bucket = new int[size];//桶（将来的所有桶都在里面分配空间）
	/*计数器，第一阶段计算某位为index的数据数量，第二阶段标记每个桶的结束位置*/
	int* count = new int[10];
	if (bucket == NULL || count == NULL)
	{
		cerr << "内存空间不足！" << endl;
		exit(1);
	}

	for (int i = 0, radixNum = 1;i < max;++i)//按位数进行max次排序，radixNum为基数
	{
		for (int j = 0;j < 10;++j)//每次排序前初始化计数器
			count[j] = 0;
		for (int j = 0;j < size;++j)
		{
			/*拿到数据第i位上的数字作为索引*/
			int index = (copyGroup[j] / radixNum) % 10;
			++count[index];//数据量加1
		}
		for (int j = 1;j < 10;++j)//为每个桶分配空间
			count[j] = count[j - 1] + count[j];//桶的结束位置

		for (int j = size - 1;j >= 0;--j)//将数据放入对应的桶中，保持稳定性
		{
			int index = (copyGroup[j] / radixNum) % 10;
			/*count[index]-1是数据在桶中的位置*/
			bucket[count[index] - 1] = copyGroup[j];
			--count[index];//对应数据量减1
		}
		for (int j = 0;j < size;++j)
			copyGroup[j] = bucket[j];//将桶中数据拷贝到操作数组中
		radixNum *= 10;//基数增加
	}

	delete[] bucket;
	delete[] count;
	count = bucket = NULL;
	finish = clock();

	cout << "基数排序所用时间：\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "基数排序比较次数：\t" << total << endl;
	check();
}

int Sort::maxBit()
{
	int max = 1, ruler = 10;
	while (size - 1 >= ruler)
	{
		++max;
		ruler *= 10;
	}
	return max;
}