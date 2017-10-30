#include "sort.h"

int main()
{
	cout << "**\t\t排序算法比较\t\t**" << endl;
	cout << "==========================================" << endl;
	cout << "**\t\t1 --- 冒泡排序\t\t**" << endl;
	cout << "**\t\t2 --- 选择排序\t\t**" << endl;
	cout << "**\t\t3 --- 直接插入排序\t**" << endl;
	cout << "**\t\t4 --- 希尔排序\t\t**" << endl;
	cout << "**\t\t5 --- 快速排序\t\t**" << endl;
	cout << "**\t\t6 --- 堆排序\t\t**" << endl;
	cout << "**\t\t7 --- 归并排序\t\t**" << endl;
	cout << "==========================================" << endl;

	cout << endl << "请输入要产生的随机数的个数：";
	int num;
	cin >> num;
	while (num < 1)
	{
		cerr << "请输入大于0小于INT_MAX的随机数个数！" << endl;
		cin.clear();
		cin >> num;
	}
	auto sort = new Sort(num);
	if (sort == NULL)
	{
		cerr << "内存空间不足！" << endl;
		exit(1);
	}

	while (1)
	{
		cout << endl << "请选择排序算法：\t";
		int operation;
		cin >> operation;

		switch (operation)
		{
		case 1:
			sort->bubble();
			break;
		case 2:
			sort->selection();
			break;
		case 3:
			sort->insertion();
			break;
		case 4:
			sort->shell();
			break;
		case 5:
			sort->quick();
			break;
		case 6:
			sort->heap();
			break;
		case 7:
			sort->merge();
			break;
		default:
			return 0;
		}
	}
}