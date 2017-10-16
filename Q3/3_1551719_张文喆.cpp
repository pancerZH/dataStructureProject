#include "knight.h"

int main()
{
	auto knight = new Knight(1, 1, 5, 5);
	auto field = new Field();

	field->showMap();
	knight->findWay(field);
	knight->showAll();
	
	getchar();
	return 0;
}