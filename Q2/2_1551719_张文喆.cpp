#include "circle.h"

int main()
{
	int totalNum, startNum, deathNum,leftNum;
	cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一人开始报数，如此循环，直至剩下K个人为止。" << endl;
	cout << endl << "请输入生死游戏的总人数N：";
	cin >> totalNum;
	cout << "请输入游戏开始的位置S：";
	cin >> startNum;
	cout << "请输入死亡数字M：";
	cin >> deathNum;
	cout << "请输入剩余的生者人数K：";
	cin >> leftNum;

	auto circle = new Circle(totalNum, startNum, deathNum, leftNum);
	circle->killUntilLeftNum();
	circle->showAll();

	getchar();
	getchar();
	return 0;
}