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
	void quickSort(const int, const int);//����������Ӻ��������ڵݹ�
	void heap();//������
	void percDown(const int, const int);//��������Ӻ��������ڿ�Ѩ����
	void merge();//�鲢����
	void divideMerge(int*, const int, const int);//�鲢������Ӻ��������ڻ�������
	void mergeTwoPart(int*, int, int, int);//�鲢������Ӻ��������ںϲ�����������ı�
	void bucket();//Ͱ����
	void radix();//��������
	int maxBit();//��������ĸ�����������ȡ���ݵ����λ��
private:
	int size;
	int* numGroup;
	int* copyGroup;
	int total;//����ʱ�Ľ�������
};

Sort::Sort(const int size)
	:size(size), total(0)
{
	numGroup = new int[size];
	copyGroup = new int[size];
	if (numGroup == NULL || copyGroup == NULL)
	{
		cerr << "�ڴ�ռ䲻�㣡" << endl;
		exit(1);
	}

	srand(int(time));
	for (int i = 0;i < size;++i)
		/*��֤���ɵ��������С��ΧΪ0~size-1*/
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
	this->total = 0;//����������0
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
	this->total = 0;//����������0
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
	this->total = 0;//����������0
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
	this->total = 0;//����������0
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
	this->total = 0;//����������0
	clock_t start, finish;

	start = clock();
	quickSort(0, size - 1);
	finish = clock();

	cout << "������������ʱ�䣺\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "�������򽻻�������\t" << total << endl;
	check();
}

void Sort::quickSort(const int left, const int right)
{
	int i = left, j = right;//�ֱ�ָ�������ͷβ
	if (right - left <= 20)//�����ݽ���ʱ����ֱ�Ӳ�������
	{
		for (int i = left;i <= right;++i)
		{
			/*�����ÿ��ѭ����Ҫ����i��Ԫ���Ƿ���Է��ڵ�j-1��Ԫ��֮ǰ*/
			/*����ǰi-1��Ԫ���Ѿ��ź�������һ�������޷�������ǰ�ƶ�����ֹͣѭ��*/
			for (int j = i;j > 0 && copyGroup[j - 1] > copyGroup[j];--j)
			{
				swap(copyGroup[j], copyGroup[j - 1]);//ÿ�ν���i��Ԫ����ǰ�ƶ�
				++total;
			}
		}
		return;
	}

	int index = left + (rand() % (right - left + 1));
	int key = copyGroup[index];//�ҵ���׼Ԫ
	swap(copyGroup[index], copyGroup[right]);//����׼Ԫ����������򲿷�
	--j;
	while (i <= j)
	{
		while (key < copyGroup[j])
			--j;//�ҵ��Ҳ��һ��С�ڻ�׼Ԫ����
		while (key > copyGroup[i])
			++i;//�ҵ�����һ�����ڻ�׼Ԫ����
		if (i < j)//�������δ�����򽻻����ǵ�ֵ
		{
			swap(copyGroup[i], copyGroup[j]);
			++total;
			++i;
			--j;
		}
		else//���������˳�ѭ��
			break;
	}
	swap(copyGroup[i], copyGroup[right]);//��׼Ԫ��λ
	++total;

	quickSort(left, i - 1);//����������벿��
	quickSort(i + 1, right);//���������Ұ벿��
}

void Sort::heap()
{
	copyNumGroup();//�����ݸ��Ƶ�����������
	this->total = 0;//����������0
	clock_t start, finish;

	start = clock();
	for (int i = size / 2;i >= 0;--i)//����,����Ԫ��λ�ڸ���
		percDown(i, size);
	for (int i = size - 1;i > 0;--i)
	{
		/*���������Ԫ������������ͷ����������������Ϊ��С����*/
		swap(copyGroup[i], copyGroup[0]);
		++total;
		percDown(0, i);
	}
	finish = clock();

	cout << "����������ʱ�䣺\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "�����򽻻�������\t" << total << endl;
	check();
}

void Sort::percDown(const int downIndex, const int endIndex)
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

void Sort::merge()
{
	copyNumGroup();//�����ݸ��Ƶ�����������
	this->total = 0;//�Ƚϼ�����0
	clock_t start, finish;

	start = clock();
	int* tempArr = new int[size];
	if (tempArr == NULL)
	{
		cerr << "�ڴ�ռ䲻�㣡" << endl;
		exit(1);
	}

	divideMerge(tempArr, 0, size - 1);
	delete[] tempArr;
	tempArr = NULL;
	finish = clock();

	cout << "�鲢��������ʱ�䣺\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "�鲢����Ƚϴ�����\t" << total << endl;
	check();
}

void Sort::divideMerge(int* tempArr, const int left, const int right)
{
	int center;
	if (left < right)//����Ĳ��ֿ��Լ�������
	{
		center = (left + right) / 2;
		/*����Ϊleft~center���֣�center��Ϊ�µ�right*/
		divideMerge(tempArr, left, center);
		/*����Ϊcenter+1~right���֣�center+1��Ϊ�µ�left*/
		divideMerge(tempArr, center + 1, right);
		/*�������ֺϲ�*/
		mergeTwoPart(tempArr, left, center + 1, right);
	}
}

void Sort::mergeTwoPart(int* tempArr, int left, int right, int rightEnd)
{
	int leftEnd = right - 1;//��߲��ֵĽ�βλ��rightǰһλ
	int tempPos = left;//��ʱ���������λ��
	int numOfElem = rightEnd - left + 1;//����������Ԫ�ص�����

	while (left <= leftEnd && right <= rightEnd)//����һ����δ�������ʱ
	{
		++total;
		if (copyGroup[left] < copyGroup[right])//�ҳ������������ж�Ӧλ���Ͻ�С��
			tempArr[tempPos++] = copyGroup[left++];//����������ϵ����ַ�����ʱ����
		else
			tempArr[tempPos++] = copyGroup[right++];
	}

	/*��������whileֻ����ִ��һ����Ŀ���ǽ�δ�������Ǹ����������ʱ����*/
	while (left <= leftEnd)//���������ʣ�ಿ��˳�������ʱ����
		tempArr[tempPos++] = copyGroup[left++];
	while (right <= rightEnd)//���ұ�����ʣ�ಿ��˳�������ʱ����
		tempArr[tempPos++] = copyGroup[right++];

	/*������õ�Ԫ�ش���ʱ�����п����ز�������*/
	for (int i = 0;i < numOfElem;++i, --rightEnd)
		copyGroup[rightEnd] = tempArr[rightEnd];
}

void Sort::bucket()
{
	copyNumGroup();//�����ݸ��Ƶ�����������
	this->total = 0;//�Ƚϼ�����0
	clock_t start, finish;

	start = clock();
	int* bucket = new int[size];//����Ͱ�ռ�
	if (bucket == NULL)
	{
		cerr << "�ڴ�ռ䲻�㣡" << endl;
		exit(1);
	}
	/*��Ͱ��Ԫ�ظ�ֵΪ0*/
	for (int i = 0;i < size;++i)
		bucket[i] = 0;

	/*��������Ԫ�ط���Ͱ��*/
	for (int i = 0;i < size;++i)
		++bucket[copyGroup[i]];

	/*��Ͱ��Ԫ�ذ�˳��Żز�������*/
	int pos = 0;
	for (int i = 0;i < size;++i)
		for (int j = bucket[i];j > 0;--j)
			copyGroup[pos++] = i;
	delete[] bucket;
	finish = clock();

	cout << "Ͱ��������ʱ�䣺\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "Ͱ����Ƚϴ�����\t" << total << endl;
	check();
}

void Sort::radix()//LSD����ʵ��
{
	copyNumGroup();//�����ݸ��Ƶ�����������
	this->total = 0;//�Ƚϼ�����0
	clock_t start, finish;

	start = clock();
	int max = maxBit();
	int* bucket = new int[size];//Ͱ������������Ͱ�����������ռ䣩
	/*����������һ�׶μ���ĳλΪindex�������������ڶ��׶α��ÿ��Ͱ�Ľ���λ��*/
	int* count = new int[10];
	if (bucket == NULL || count == NULL)
	{
		cerr << "�ڴ�ռ䲻�㣡" << endl;
		exit(1);
	}

	for (int i = 0, radixNum = 1;i < max;++i)//��λ������max������radixNumΪ����
	{
		for (int j = 0;j < 10;++j)//ÿ������ǰ��ʼ��������
			count[j] = 0;
		for (int j = 0;j < size;++j)
		{
			/*�õ����ݵ�iλ�ϵ�������Ϊ����*/
			int index = (copyGroup[j] / radixNum) % 10;
			++count[index];//��������1
		}
		for (int j = 1;j < 10;++j)//Ϊÿ��Ͱ����ռ�
			count[j] = count[j - 1] + count[j];//Ͱ�Ľ���λ��

		for (int j = size - 1;j >= 0;--j)//�����ݷ����Ӧ��Ͱ�У������ȶ���
		{
			int index = (copyGroup[j] / radixNum) % 10;
			/*count[index]-1��������Ͱ�е�λ��*/
			bucket[count[index] - 1] = copyGroup[j];
			--count[index];//��Ӧ��������1
		}
		for (int j = 0;j < size;++j)
			copyGroup[j] = bucket[j];//��Ͱ�����ݿ���������������
		radixNum *= 10;//��������
	}

	delete[] bucket;
	delete[] count;
	count = bucket = NULL;
	finish = clock();

	cout << "������������ʱ�䣺\t" << float(finish - start) / CLOCKS_PER_SEC << endl;
	cout << "��������Ƚϴ�����\t" << total << endl;
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