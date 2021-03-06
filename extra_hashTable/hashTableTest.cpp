#include "hashTable.h"

void testSepchain();
void testOpenchain();
void testRehashchain();

int main()
{
	testSepchain();
	testOpenchain();
	testRehashchain();

	return 0;
}

void testSepchain()
{
	const int size = 10;
	auto test = new Sepchain(size);

	int count = 19;
	while (count >= 0)
	{
		test->addNum(count*count);
		--count;
	}
	test->removeNum(49);
	test->removeNum(9);
	test->addNum(0);
	test->addNum(12);

	cout << "separate chaining:" << endl << endl;
	test->showAll();
	getchar();
}

void testOpenchain()
{
	const int size = 10;
	auto test = new Openchain(size);

	test->lineDetect(89);
	test->lineDetect(18);
	test->lineDetect(49);
	test->lineDetect(58);
	test->lineDetect(69);

	cout << endl << "line detection result:" << endl << endl;
	test->showAll();
	delete test;
	test = NULL;

	test = new Openchain(size);
	test->squareDetect(89);
	test->squareDetect(18);
	test->squareDetect(49);
	test->squareDetect(58);
	test->squareDetect(69);

	cout << endl << "square detection result:" << endl << endl;
	test->showAll();
	delete test;
	test = NULL;

	test = new Openchain(size);
	test->doubleHash(89);
	test->doubleHash(18);
	test->doubleHash(49);
	test->doubleHash(58);
	test->doubleHash(69);

	cout << endl << "double hashing result:" << endl << endl;
	test->showAll();
	delete test;
	test = NULL;

	getchar();
}

void testRehashchain()
{
	const int capacity = 7;
	auto test = new Rehashchain(capacity);

	test->insert(13);
	test->insert(15);
	test->insert(24);
	test->insert(6);

	cout << endl << "rehashing table_1:" << endl << endl;
	test->showAll();
	test->insert(23);
	cout << endl << "rehashing table_2:" << endl << endl;
	test->showAll();
	delete test;
	test = NULL;

	getchar();
}