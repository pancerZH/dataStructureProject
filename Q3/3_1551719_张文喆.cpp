#include "knight.h"

int main()
{
	auto knight = new Knight(1, 1, 5, 5);
	auto field = new Field();
	if (knight == NULL || field == NULL)
	{
		cerr << "¿Õ¼ä²»×ã£¡" << endl;
		exit(1);
	}

	knight->findWay(field);
	knight->drawSolutionOnMap(field);
	field->showMap();
	knight->showAll();
	
	getchar();
	return 0;
}