#include <iostream>
#include <ctime>

using namespace std;

class Sort {
	/*һ�ɰ��մ�С�����˳������*/
public:
	Sort(const int);
	void copyNumGroup();//�����ɵ����鿽��������������
	void swap(int&, int&);//�����ṩ������Ԫ��
	bool check();//��������Ƿ���ȷ
	void show();//��ӡ����������
	void bubble();//ð������
	void selection();//ѡ������
	void insertion();//ֱ�Ӳ�������
	void shell();//ϣ������
	void quick();//��������
	void quickSort(const int, const int, int&);//����������Ӻ��������ڵݹ�
	void heap();//������
	void percDown(const int, const int, int&);//��������Ӻ��������ڿ�Ѩ����
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
		cerr << "�ڴ�ռ䲻�㣡" << endl;
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
		if (copyGroup[i] > copyGroup[i + 1])//����δ�ź��������
		{
			cout << "����ʧ�ܣ�" << endl;
			return false;
		}
	}
	cout << "����ɹ���" << endl;
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
	copyNumGroup();//�����ݸ��Ƶ�����������
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

	cout << "ð����������ʱ�䣺\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "ð�����򽻻�������\t" << total << endl;
	check();
	//show();
}

void Sort::selection()
{
	copyNumGroup();//�����ݸ��Ƶ�����������
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
			}
		}

		swap(copyGroup[i], copyGroup[position]);
		++total;
	}
	finish = clock();

	cout << "ѡ����������ʱ�䣺\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "ѡ�����򽻻�������\t" << total << endl;
	check();
	//show();
}

void Sort::insertion()
{
	copyNumGroup();//�����ݸ��Ƶ�����������
	int total = 0;
	clock_t start, finish;

	start = clock();
	for (int i = 0;i < size;++i)
	{
		/*�����ÿ��ѭ����Ҫ����i��Ԫ���Ƿ���Է��ڵ�j-1��Ԫ��֮ǰ*/
		/*����ǰi-1��Ԫ���Ѿ��ź�������һ�������޷�������ǰ�ƶ�����ֹͣѭ��*/
		for (int j = i;j > 0 && copyGroup[j - 1] > copyGroup[j];--j)
		{
			swap(copyGroup[j], copyGroup[j - 1]);//ÿ�ν���i��Ԫ����ǰ�ƶ�
			++total;
		}
	}
	finish = clock();

	cout << "ֱ�Ӳ�����������ʱ�䣺\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "ֱ�Ӳ������򽻻�������\t" << total << endl;
	check();
}

void Sort::shell()
{
	copyNumGroup();//�����ݸ��Ƶ�����������
	int total = 0;
	clock_t start, finish;

	int k, product = 1;
	for (k = 0;product * 2 - 1 <= size;++k)//�ҵ�Hibbard�����Ͻ�
		product *= 2;

	start = clock();
	for (int increment = product - 1;increment > 0;product /= 2, increment = product - 1)
	{
		/*ϣ�������ڲ�ʹ�ò������򣬲��ҿ��Ա�֤ǰi��������increment-�����*/
		for (int i = increment;i < size;++i)
		{
			for (int j = i;j >= increment;j -= increment)
			{
				if (copyGroup[j] < copyGroup[j - increment])
				{
					swap(copyGroup[j], copyGroup[j - increment]);
					++total;
				}
				else//�Ѿ��ź�����
					break;
			}
		}
	}
	finish = clock();

	cout << "ϣ����������ʱ�䣺\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "ϣ�����򽻻�������\t" << total << endl;
	check();
}

void Sort::quick()
{
	copyNumGroup();//�����ݸ��Ƶ�����������
	int total = 0;
	clock_t start, finish;

	start = clock();
	quickSort(0, size - 1, total);
	finish = clock();

	cout << "������������ʱ�䣺\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "�������򽻻�������\t" << total << endl;
	check();
}

void Sort::quickSort(const int left, const int right, int& total)
{
	int i = left, j = right;//�ֱ�ָ�������ͷβ
	if (left > right)
		return;

	int key = copyGroup[left];//�ҵ���׼Ԫ
	while (i != j)
	{
		while (j > i&&key <= copyGroup[j])
			--j;//�ҵ��Ҳ��һ��С�ڻ�׼Ԫ����
		while (i < j&&key >= copyGroup[i])
			++i;//�ҵ�����һ�����ڻ�׼Ԫ����
		if (i < j)//�������δ�ص����򽻻����ǵ�ֵ
		{
			swap(copyGroup[i], copyGroup[j]);
			++total;
		}
	}
	swap(copyGroup[i], copyGroup[left]);//��׼Ԫ��λ
	++total;

	quickSort(left, i - 1, total);//����������벿��
	quickSort(i + 1, right, total);//���������Ұ벿��
}

void Sort::heap()
{
	copyNumGroup();//�����ݸ��Ƶ�����������
	int total = 0;
	clock_t start, finish;

	start = clock();
	for (int i = size / 2;i >= 0;--i)//����,����Ԫ��λ�ڸ���
		percDown(i, size, total);
	for (int i = size - 1;i > 0;--i)
	{
		/*���������Ԫ������������ͷ����������������Ϊ��С����*/
		swap(copyGroup[i], copyGroup[0]);
		++total;
		percDown(0, i, total);
	}
	finish = clock();

	cout << "����������ʱ�䣺\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "�����򽻻�������\t" << total << endl;
	check();
}

void Sort::percDown(const int downIndex, const int endIndex, int& total)
{
	int childIndex;//����ָ�����������нϴ����һ��
	for (int i = downIndex;2 * i + 1 < endIndex;i = childIndex)
	{
		childIndex = 2 * i + 1;//����ָʾ��������ӵ�����
		/*���ڵ�ǰ���£����Ҷ��Ӵ�������ӣ���childIndex��Ϊ���������*/
		if (childIndex != endIndex - 1 && copyGroup[childIndex] < copyGroup[childIndex + 1])
			++childIndex;
		if (copyGroup[i] < copyGroup[childIndex])
		{
			swap(copyGroup[i], copyGroup[childIndex]);//Ԫ������
			++total;
		}
		else//���˵�Ԫ���ҵ��˺��ʵ�λ�ã��ָ��˶�����
			break;
	}
}