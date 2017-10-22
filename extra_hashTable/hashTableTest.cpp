#include "hashTable.h"

int main()
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
	test->showAll();

	getchar();
	return 0;
}