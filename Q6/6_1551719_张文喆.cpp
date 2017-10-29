#include "familyTree.h"

int main()
{
	cout << "**\t\t家谱管理系统\t\t**" << endl;
	cout << "==========================================" << endl;
	cout << "**\t\t请选择要执行的操作\t**" << endl;
	cout << "**\t\tA --- 完善家庭\t\t**" << endl;
	cout << "**\t\tB --- 添加家庭成员\t**" << endl;
	cout << "**\t\tC --- 解散局部家庭\t**" << endl;
	cout << "**\t\tD --- 更改家庭成员姓名\t**" << endl;
	cout << "**\t\tE --- 退出程序\t\t**" << endl;
	cout << "==========================================" << endl;

	cout << "首先建立一个家庭谱" << endl;
	cout << "请输入祖先的姓名：";
	string ancestor;
	cin >> ancestor;
	auto familyTree = new Tree(ancestor);
	if (familyTree == NULL)
	{
		cerr << "空间不足！" << endl;
		exit(1);
	}
	cout << "此家谱的祖先是：" << ancestor << endl;

	while (1)
	{
		cout << endl << "请选择要执行的操作：";
		char operation;
		cin >> operation;
		operation = toupper(operation);
		cin.clear();

		switch (operation)
		{
		case 'A':
			familyTree->addFamily();
			break;
		case 'B':
			familyTree->addOneSon();
			break;
		case 'C':
			familyTree->dismissFamily();
			break;
		case 'D':
			familyTree->changeName();
			break;
		default:
			return 0;
		}
	}
}