#include "wordCount.h"

int main()
{
	Paragraph para;

	while (1)
	{
		cout << "**************************************" << endl;
		cout << "*******�ı��ļ����ʵļ��������*******" << endl;
		cout << "======================================" << endl;
		cout << "\t��1�������ı��ĵ�\t" << endl;
		cout << "\t��2���ı����ʻ���\t" << endl;
		cout << "\t��3�����ʶ�λ\t" << endl;
		cout << "\t��4���˳�\t" << endl;
		cout << "======================================" << endl;
		cout << "��ѡ��1~4����";

		int i;
		cin >> i;
		getchar();
		switch (i)
		{
		case 1:
			para.buildPara();
			i = 4;//��i��Ϊ�˳�λ����ֹ�Ƿ������루���ַ���
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