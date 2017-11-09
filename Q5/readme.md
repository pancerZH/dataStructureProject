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
  
### 3. 类及类成员介绍

- #### Paragraph类

  - ##### 成员变量
  |成员名称|属性|类型|描述|
  |-------|----|----|---|
  |tableSize|private|int|记录散列表中单词数量|
  |table|private|Sepchain*|指向散列表的指针|

  - ##### 成员函数
  |函数名称|返回值类型|描述|
  |-------|----------|---|
  |Paragraph|无|构造函数|
  |~Paragraph|无|析构函数|
  |buildPara|bool|建立文本文档|
  |countWords|bool|统计文档中所有单词|
  |wordInLine|bool|统计特定单词的出现次数及位置|

- #### Sepchain类

  - ##### 成员变量
  |成员名称|属性|类型|描述|
  |-------|----|----|---|
  |size|private|int|散列表表头大小|
  |head|private|Node*|指向散列表表头空间的指针|

  - ##### 成员函数
  |函数名称|返回值类型|描述|
  |--------|--------|----|
  |Sepchain|无|构造函数|
  |~Sepchain|无|析构函数|
  |hash|int|将单词进行散列处理|
  |insert|bool|将单词插入散列表|
  |showAll|void|展示散列表中记录的单词信息|

- #### Linklist类

  - ##### 成员变量
  |成员名称|属性|类型|描述|
  |-------|----|---|----|
  |word|private|string|记录单词|
  |head|private|Chain*|链表的头指针|
  |size|private|int|单词在这一行出现的次数|
  |line|private|int|记录该行的行号|

  - ##### 成员函数
  |函数名称|返回值类型|描述|
  |--------|---------|---|
  |Linklist|无|构造函数|
  |~Linklist|无|析构函数|
  |insert|bool|向链表中插入新位置|
  |checkWord|void|检查一行文本中单词的出现情况|
  |showAll|void|展示单词的统计情况|

### 4. 核心代码解释

  - 创建文件并输入内容

  ```c++
  bool Paragraph::buildPara()
  {
    string fileName;
    cout << "输入要建立的文件名：";
    getline(cin, fileName);

    ofstream inFile;
    inFile.open(fileName, ios::trunc);
    if (inFile.is_open() == false)
    {
      cerr << "创建文件失败！" << endl;
      exit(2);
    }

    char c = 'n';
    while (c == 'n')
    {
      string line;
      cout << "请输入一行文本：";
      getline(cin, line);
      inFile << line << endl;

      cout << "结束输入吗？y or n";
      cin >> c;
      getchar();
    }
    inFile.close();

    return true;
  }
  ```
  该函数功能分为两部分，一是建立文件，二是写入内容。注意到不论是输入文件名还是文件内容，都采用了getline()函数完成以避免空格。

  - 统计文件中所有单词

  ```c++
  bool Paragraph::countWords()
  {
    string fileName;
    cout << "请输入文件名：";
    getline(cin, fileName);

    ifstream outFile;
    outFile.open(fileName, ios::_Nocreate);
    if (outFile.is_open() == false)
    {
      cerr << "文件不存在或打开失败！" << endl;
      return false;
    }

    if (tableSize != 0)//清除旧表
    {
      delete table;
      table = new Sepchain(HASHSIZE);//重新建立散列表
      if (table == NULL)
      {
        cerr << "空间不足！" << endl;
        exit(1);
      }
    }

    string word;
    while (outFile >> word)
    {
      if (!table->insert(word))//插入失败
        return false;
      else
        ++tableSize;
    }

    outFile.close();
    table->showAll(fileName);
    return true;
  }
  ```
  该函数工作流程分为三步，一是试图打开文件，二是清除统计先前文件的散列表，三是进行单词统计。这里的重点是单词统计。

  ```c++
  bool Sepchain::insert(const string word)
  {
    const int index = hash(word);

    Node* temp = &head[index];
    Node* previous;
    while (temp != NULL && temp->count != 0)//这个空间已有单词
    {
      if (temp->word == word)//找到了相同的单词
      {
        ++(temp->count);
        return true;
      }
      else
      {
        previous = temp;
        temp = temp->next;
      }
    }

    if (temp == NULL)//向尾部插入新节点
    {
      temp = new Node(word);
      if (temp == NULL)
      {
        cerr << "空间不足！" << endl;
        exit(1);
      }
      previous->next = temp;
      return true;
    }
    else//将head[index]更新为word
    {
      temp->word = word;
      temp->count = 1;
      return true;
    }
  }
  ```
  对散列表进行插入必须考虑两种情况，一是要插入的点没有元素，二是有元素。对于第一种情况直接插入即可，但由于这里采用了分离链接散列表，那么更多的可能是面对第二种情况。在第二种情况下，就要检查当前的元素对应的单词是否为我们正在插入的单词，如果是，那么表中单词计数加1，结束操作；否则继续检查下一个节点。如果一直检查到这条链的结尾，都没有找到同样的单词，那么这就说明我们正在插入的单词是一个全新的单词，那么我们把它插在这条链的末尾即可。

  - 检查特定单词的出现次数及位置

  ```c++
  bool Paragraph::wordInLine()
  {
    char choice;
    ...
    cin >> choice;
    getchar();

    string fileName;
    cout << "请输入文件名：";
    getline(cin, fileName);

    ifstream outFile;
    outFile.open(fileName, ios::_Nocreate);
    if (outFile.is_open() == false)
    {
      cerr << "文件不存在或打开失败！" << endl;
      return false;
    }

    string word;
    cout << "请输入要统计的单词：";
    getline(cin, word);

    string line;
    if (choice == 'a')
    {
      Linklist* list = new Linklist(word, 0);
      if (list == NULL)
      {
        cerr << "空间不足！" << endl;
        exit(1);
      }
      while (getline(outFile, line))
        list->checkWord(line);
      list->showAll(fileName, choice);
    }
    else
    {
      int i = 0;//i用于表示第i行
      while (getline(outFile, line))
      {
        ++i;
        Linklist* list = new Linklist(word, i);
        if (list == NULL)
        {
          cerr << "空间不足！" << endl;
          exit(1);
        }
        list->checkWord(line);
        list->showAll(fileName, choice);
        delete list;
      }
    }

    outFile.close();
    return true;
  }
  ```
  这里的工作分为两步：打开文件和进行统计。不过由于出现次数统计和位置统计是两个工作，我们使用choice对二者进行区分。  
  可以看到在进行出现次数统计时，我们不断地读入一行文本，并将统计结果储存在`一个`链表中，并在读取完毕后进行打印（同样的，打印也是区分两个工作的）；而在统计出现位置时，我们将一行的统计结果储存在一个链表中，打印信息后就释放掉它，并且在下一次循环中重新建立一个链表，用于面对新的一行数据。

  ```c++
  void Linklist::checkWord(const string line)
  {
    int pos = 0;
    while ((pos = line.find(word, pos)) != -1)//查找word下一个出现的位置
    {
      char wordHead;
      if (pos != 0)
        wordHead = line[pos - 1];
      else
        wordHead = SPACE;
      char wordTail = line[pos + word.length()];

      if (wordHead == SPACE && (wordTail == SPACE || wordTail == END))//保证搜索到的是一个单词而不是单词的一部分字母
      {
        insert(pos);
      }
      pos += word.length();
    }
  }
  ```
  这里使用了string类中的成员函数find()进行查找单词，但是这会造成一个问题：有些完整单词的子序列也会被查找出来。举个例子，查找单词interest时，如果文本中包含单词interesting，那么这个find函数也是会返回interesting单词的起始位置的。为了避免这种情况，我们必须检查返回的这个位置是不是确实是我们要找的单词，解决方案是检查这个要查找的单词的长度的前后位置是否为空格。当然我们也要考虑到单词位于句首的情况（这时单词的是没有“前面”的）。

  ### 5. 容错测试

  容错较为简单，主要是在非创建文件下打开文件失败的情况。其他的诸如查询不存在的单词、将子序列识别为单词的情况已在程序设计中识别并解决。