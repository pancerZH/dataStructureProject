#include "circle.h"

int main()
{
	int totalNum, startNum, deathNum,leftNum;
	cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一人开始报数，如此循环，直至剩下K个人为止。" << endl;
	cout << endl << "请输入生死游戏的总人数N：";
	cin >> totalNum;
	while (totalNum < 1)
	{
		cout << "请输入大于0小于INT_MAX的总人数！" << endl;
		cin.clear();
		cin.ignore();
		cin >> totalNum;
	}

	cout << "请输入游戏开始的位置S：";
	cin >> startNum;
	while (startNum < 1 || startNum > totalNum)
	{
		cout << "请输入大于0小于等于总人数的开始位置！" << endl;
		cin.clear();
		cin.ignore();
		cin >> startNum;
	}

	cout << "请输入死亡数字M：";
	cin >> deathNum;
	while (deathNum < 1 || deathNum > totalNum)
	{
		cout << "请输入大于0小于等于总人数N的死亡数字M！" << endl;
		cin.clear();
		cin.ignore();
		cin >> deathNum;
	}

	cout << "请输入剩余的生者人数K：";
	cin >> leftNum;
	while (leftNum < 0 || leftNum > totalNum)
	{
		cout << "请输入大于等于0小于等于总人数N的剩余生者人数K！" << endl;
		cin.clear();
		cin.ignore();
		cin >> leftNum;
	}

	auto circle = new Circle(totalNum, startNum, deathNum, leftNum);
	if (circle == NULL)
	{
		cerr << "空间不足！" << endl;
		exit(1);
	}
	circle->killUntilLeftNum();
	circle->showAll();

	getchar();
	getchar();
	return 0;
}