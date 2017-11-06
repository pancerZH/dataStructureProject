#include "disjointUnion.h"

int main()
{
	auto union1 = Union(8);
	union1.setUnion(4, 5);
	union1.setUnion(6, 7);
	union1.setUnion(4, 6);
	union1.setUnion(3, 4);
	union1.showUnion();
	getchar();
}