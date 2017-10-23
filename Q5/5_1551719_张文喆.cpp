#include "wordCount.h"

int main()
{
	Paragraph para;

	while (1)
	{
		cout << "**************************************" << endl;
		cout << "*******文本文件单词的检索与计数*******" << endl;
		cout << "======================================" << endl;
		cout << "\t【1】建立文本文档\t" << endl;
		cout << "\t【2】文本单词汇总\t" << endl;
		cout << "\t【3】单词定位\t" << endl;
		cout << "\t【4】退出\t" << endl;
		cout << "======================================" << endl;
		cout << "请选择（1~4）：";

		int i;
		cin >> i;
		getchar();
		switch (i)
		{
		case 1:
			para.buildPara();
			i = 4;//将i置为退出位，防止非法的输入（如字符）
			break;
		case 2:
			para.countWords();
			i = 4;
			break;
		case 3:
			para.wordInLine();
			i = 4;
			break;
		default:
			return 0;
			break;
		}
	}
}