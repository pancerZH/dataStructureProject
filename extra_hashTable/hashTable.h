#include <iostream>

using namespace std;

/*==================================以下为分离链接散列表的实现==================================*/

class Node {
public:
	Node(const int num)
		:num(num), next(NULL) {}
	int num;
	Node* next;
};

class Sepchain {
public:
	Sepchain(const int);
	~Sepchain();
	int hash(const int num) { return (num % 10); }
	bool addNum(const int);
	bool removeNum(const int);
	void showAll();
private:
	Node* head;
	int size;
};

Sepchain::Sepchain(const int size)
	:size(size)
{
	head = (Node*)malloc(sizeof(Node) * size);//申请size个Node大小的空间
	if (head == NULL)
	{
		cerr << "内存不足！" << endl;
		return;
	}

	for (int i = 0;i < size;++i)//将这size个Node初始化
	{
		head[i].num = size;
		head[i].next = NULL;
	}
}

Sepchain::~Sepchain()
{
	for (int i = 0;i < size;++i)
	{
		Node* currentNode = head[i].next;
		while (currentNode != NULL)
		{
			Node* temp = currentNode;
			currentNode = currentNode->next;
			delete temp;
			temp = NULL;
		}
	}
	free(head);
}

bool Sepchain::addNum(const int num)
{
	Node* addNode = new Node(num);
	if (addNode == NULL)
	{
		cerr << "内存不足！" << endl;
		return false;
	}

	const int index = hash(num);
	Node* temp = &head[index];
	while (temp->num != num && temp->next != NULL)//防止表中元素重复
		temp = temp->next;
	if (temp->num == num)//出现了重复
	{
		delete addNode;
		return true;
	}
	temp->next = addNode;

	return true;
}

bool Sepchain::removeNum(const int num)
{
	const int index = hash(num);
	Node* temp = &head[index];
	Node* previous = temp;
	while (temp != NULL && temp->num != num)
	{
		previous = temp;
		temp = temp->next;
	}

	if (temp == NULL)//未找到要删除的元素
		return false;
	else//找到了要删除的元素
	{
		previous->next = temp->next;
		delete temp;
		temp = NULL;
		return true;
	}
}

void Sepchain::showAll()
{
	for (int i = 0;i < size;++i)
	{
		cout << i << " : ";
		Node* temp = head[i].next;
		while (temp != NULL)
		{
			cout << temp->num << " --> ";
			temp = temp->next;
		}
		cout << "NULL" << endl;
	}
}

/*==================================以上为分离链接散列表的实现==================================*/

/*==================================以下为开放定址散列表的实现==================================*/

class Block {
public:
	Block() :isEmpty(true) {}
	bool isEmpty;
	int num;
};

class Openchain {
public:
	Openchain(const int);
	~Openchain() { delete[] head; }
	int hash(const int num) { return (num%size); }
	int hash2(const int num) { return (R - num%R); }
	bool lineDetect(const int);
	bool squareDetect(const int);
	bool doubleHash(const int);
	void showAll();
private:
	int size;
	Block* head;
	int R;
};

Openchain::Openchain(const int size)
	:size(size), R(7)
{
	//head = (Block*)malloc(sizeof(Block)*size);
	//上面这种方法无法初始化Block对象
	head = new Block[size];
	if (head == NULL)
	{
		cerr << "内存不足！" << endl;
		return;
	}
}

bool Openchain::lineDetect(const int num)
{
	const int index = hash(num);
	for (int temp = index;temp + 1 != index;++temp)
	{
		if (temp == size)//越界之后返回0处
			temp = 0;
		
		if (head[temp].isEmpty == true)
		{
			head[temp].isEmpty = false;
			head[temp].num = num;
			return true;
		}
	}
	return false;//表已满
}

bool Openchain::squareDetect(const int num)
{
	const int index = hash(num);
	if (head[index].isEmpty == true)
	{
		head[index].isEmpty = false;
		head[index].num = num;
		return true;
	}

	int temp = -1 ,count = 1;
	while (temp != index)
	{
		temp = index + count*count;
		++count;

		if (temp >= size)//越界之后折回起点
			temp -= size;

		if (head[temp].isEmpty == true)
		{
			head[temp].isEmpty = false;
			head[temp].num = num;
			return true;
		}
	}
	return false;
}

bool Openchain::doubleHash(const int num)
{
	const int index = hash(num);
	if (head[index].isEmpty == true)
	{
		head[index].isEmpty = false;
		head[index].num = num;
		return true;
	}

	const int gap = hash2(num);
	for (int i = 1, temp = index + i*gap;temp != index;temp = index + i*gap)
	{
		if (temp >= size)//越界之后折回起点
			temp -= size;

		if (head[temp].isEmpty == true)
		{
			head[temp].isEmpty = false;
			head[temp].num = num;
			return true;
		}
	}
	return false;
}

void Openchain::showAll()
{
	for (int i = 0;i < size;++i)
	{
		cout << i << " : ";
		if (head[i].isEmpty == false)
			cout << head[i].num << endl;
		else
			cout << "NULL" << endl;
	}
}

/*==================================以上为开放定址散列表的实现==================================*/

/*==================================以下为再散列散列表的实现==================================*/

class Rehashchain {
public:
	Rehashchain(const int);
	~Rehashchain() { delete[] head; }
	int hash(const int num) { return (num%capacity); }
	bool insert(const int);
	bool rehash();
	int getMaxPrime(int);
	void showAll();
private:
	int size;
	int capacity;
	float lambda;
	Block* head;
};

Rehashchain::Rehashchain(const int capacity)
	:size(0), capacity(capacity), lambda(0)
{
	head = new Block[capacity];
	if (head == NULL)
	{
		cerr << "内存不足！" << endl;
		return;
	}
}

bool Rehashchain::insert(const int num)//使用线性探测
{
	const int index = hash(num);
	for (int temp = index;temp + 1 != index;++temp)
	{
		if (temp == capacity)//越界之后返回0处
			temp = 0;

		if (head[temp].isEmpty == true)
		{
			head[temp].isEmpty = false;
			head[temp].num = num;
			++size;
			lambda = (float)size / (float)capacity;

			if(lambda > 0.7)
				rehash();
			return true;
		}
	}
	return false;//表已满
}

bool Rehashchain::rehash()
{
	capacity = getMaxPrime(capacity * 2);
	Block* temp = head;
	head = new Block[capacity];
	if (head == NULL)
	{
		cerr << "内存不足！" << endl;
		return false;
	}
	
	int i = 0, count = size;
	size = 0;
	while (count)
	{
		if (temp[i].isEmpty == false)
		{
			insert(temp[i].num);
			--count;
		}
		++i;
	}
	return true;

}

int Rehashchain::getMaxPrime(int num)//保证num是偶数（num = 2*capacity）
{
	if(num != 2)//2是素数
		num += 1;//将num变为奇数
	int prime = num;

	while (1)
	{
		int i;
		for (i = 2;i < sqrt(prime);++i)
		{
			if (prime % i == 0)//不是素数
				break;
		}
		if (i > sqrt(prime))
			return prime;
		else
			prime += 2;//素数必不为偶数
	}
}

void Rehashchain::showAll()
{
	for (int i = 0;i < capacity;++i)
	{
		cout << i << " : ";
		if (head[i].isEmpty == false)
			cout << head[i].num << endl;
		else
			cout << "NULL" << endl;
	}
}