# 数据结构课程设计

#### 作者：张文喆

## 单词检索统计系统

### 0. 项目简介  
给定一个文本文件，要求统计给定单词在文本中出现的总次数，并检索输出某个单词出现在文本中的行号、在该行中出现的次数以及位置。

### 1. 项目运行效果

- 建立文件

  使用标准库中的ofstream建立、读取和写入文件。  
  ```c++
  ofstream inFile;
	inFile.open(fileName, ios::trunc);
	if (inFile.is_open() == false)
	{
		cerr << "创建文件失败！" << endl;
		exit(2);
	}
  ```
  值得注意的是，这里使用的模式为ios::trunc，所以如果存在同名文件，则该文件中的内容会被清空。
  
- 统计所有单词

  由Paragraph::countWords()函数完成。这里因为需要统计所有单词，所以为了保证速度，使用了散列表储存单词。
  ```c++
  string word;
	while (outFile >> word)
	{
		if (!table->insert(word))//插入失败
			return false;
		else
			++tableSize;
	}
  ```
  散列表为分离链接散列表。
  
- 统计特定单词

  由Paragraph::wordInLine()函数完成。并且统计特定单词时需要以行为单位对文件进行遍历，所以不再需要使用散列表统计所有单词。这里采用了一个链表记录
  特定单词在某行的出现位置和出现次数。根据具体选项的不同（统计出现次数或是出现位置），打印不同的内容。
  在统计出现次数时，采用的方法是将全文中该单词的位置全部插入一个链表进行统计；在统计出现位置时，采用的是逐行储存出现位置，并且在一行检索完毕后进行输出，
  释放链表占用的空间，在下一次循环开头建立新的链表进行统计。
  
- 运行截屏

  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q5/image/buildFile.PNG)
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q5/image/totalWords.PNG)
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q5/image/timeCount.PNG)
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q5/image/positionCheck.PNG)
  
### 2. 概述

- 项目要求  

  本项目的设计要求可以分为三个部分实现：  
  其一，建立一个文本文件，文件名由用户用键盘输入；  
  其二，给定单词计数，输入一个不含空格的单词，统计输出该单词在文本中的出现次数；  
  其三，检索给定单词，输入一个单词，检索并输出该单词所在的行号、该行中出现的次数以及在该行中的相应位置。 
  
- 实现方法

  主要是练习散列表和链表的使用；实际上链表是用来模拟栈的。
  
