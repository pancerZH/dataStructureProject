# 数据结构课程设计

#### 作者：张文喆

## 约瑟夫生死环游戏

### 0. 项目简介  
约瑟夫生者死者游戏的大意是：30个旅客同乘一条船，因为严重超载，加上风高浪大，危险万分；因此船长告诉乘客，只有将全船一半的旅客投入海中，其余人才能幸免于难。  
无奈，大家只得统一这种方法，并议定 30 个人围成一圈，由第一个人开始，依次报数，数到第9人，便将他投入大海中，然后从他的下一个人数起，数到第 9 人，再将他投入大海，如此循环，直到剩下15个乘客为止。  
问哪些位置是将被扔下大海的位置。 

### 1. 项目运行效果

- 建立生死环  

  按照题目要求，程序在开始运行后，会要求输入四个量，分别为：  
  - 总人数N  
  - 游戏开始位置S  
  - 死亡数字M（即数到第M人）  
  - 剩余生者人数K  
  
  代码为：  
  
  ```c++
  auto circle = new Circle(totalNum, startNum, deathNum, leftNum);
	if (circle == NULL)
	{
		cerr << "空间不足！" << endl;
		exit(1);
	}
  ```
  
  其中，totalNum，startNum，deathNum，leftNum分别对应N，S，M，K  
  
- 开始游戏

  按照之前输入的信息，根据生死环的规则开始运行游戏  
  
  代码为：  
  
  ```c++
  circle->killUntilLeftNum();
  ```
  
- 展示结果  

  最后展示死者位置和生还者数量、位置  
  
  代码：  
  
  ```c++
  circle->showAll();
  ```
  
- 运行截图  

  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q2/image/run.PNG)
  
  （与题目演示中的运行结果一致）  
  
### 2. 概述  

- #### 项目要求及建议  

  本游戏的数学建模如下：假如 N 个旅客排成一个环形，依次顺序编号 1, 2, …, N。  
  从某个指定的第 S 号开始。沿环计数，每数到第 M 个人就让其出列，且从下一个人开始重新计数，继续进行下去。  
  这个过程一直进行到剩下K个旅客为止。  
  本游戏要求用户输入的内容包括：  
  1. 旅客的个数，也就是 N 的值；  
  2. 离开旅客的间隔数，也就是 M 的值；  
  3. 所有旅客的序号作为一组数据要求存放在某种数据结构中。  
  
  本游戏要求输出的内容是包括：
  1. 离开旅客的序号；  
  2. 剩余旅客的序号。
  
- #### 实现方法  

  采用了双向循环链表实现，但事实上并没有用到`双向`这一性质，起到的作用与单向循环链表相同  
  其中，链表的节点由`Passenger`类的对象组成，链表的头结点和操作则由`Circle`类对象完成  
  
### 3. 类及类成员介绍

- #### Passenger类
  
  - ##### 成员变量
  |成员名称 |属性|类型|描述|
  |--------|----|---|----|
  |next|public|Passenger*|指向下一个乘客的指针|
  |front|public|Passenger*|指向上一个乘客的指针|
  |ID|private|int|乘客编号（即所处位置）|
  
  - ##### 成员函数
  |函数名称|返回值类型|描述|
  |-------|---------|----|
  |Passenger|无|构造函数|
  |getID|int|返回乘客的ID|
  |linkNext|bool|链接下一个乘客节点，成功返回true；失败返回false|
 
- ### Circle类

  - ##### 成员变量
  |成员名称 |属性|类型|描述|
  |--------|----|---|----|
  |head|Passenger*|private|指向链表的头指针|
  |totalNum|int|private|乘客总人数（链表初始大小）|
  |deathNum|int|private|死亡数字|
  |leftNum|int|private|最终剩余生者人数|
  
  - ##### 成员函数
  |函数名称|返回值类型|描述|
  |-------|---------|----|
  |Circle|无|构造函数|
  |~Circle|无|析构函数，释放掉链表占用的空间|
  |killUntilLeftNum|bool|调用杀人函数，直到剩余人数为leftNum|
  |killSomeone|Passenger*|杀掉某个位置上的乘客，并且返回指向下一个乘客的指针|
  |showAll|void|展示生者人数、位置|

### 4. 核心代码解释    

- #### 建立生死环

  建立生死环包括两个步骤：  
  1. 建立循环链表；  
  2. 找到起始乘客的位置  
  
  ```c++
  Circle::Circle(int num, int start, int deathNum, int leftNum)
	{
		head = new Passenger(1);//建立生死环
		...
		Passenger* temp = head;
		int count = 2;
		while (count <= num)
		{
			temp->linkNext(new Passenger(count));
			if(temp->next != NULL)
				temp = temp->next;
			++count;
		}
		temp->linkNext(head);//构成双向循环链表

		while (start > 1)//找到起始旅客位置
		{
			head = head->next;
			--start;
		}
		...
	}
  ```
  
  其中，调用的linkNext函数为  
  
  ```c++
  bool Passenger::linkNext(Passenger* nextPassenger)
  {
    if (nextPassenger != NULL)
    {
      this->next = nextPassenger;
      nextPassenger->front = this;
      return true;
    }
    else
    {
      cerr << "内存空间不足！" << endl;
      exit(1);
    }
  }
  ```
  可见，linkNext函数除了链接下一个节点外，还对Circle函数中对空间的申请进行了检查，防止出现内存不足的情况。  
  
- #### 杀掉乘客  
  
  杀掉乘客时，采用的方法是由当前指针所指乘客为起点，找到他之后的第deathNum个人，并将他杀掉  

  ```c++
  bool Circle::killUntilLeftNum()
  {
    Passenger* temp = head;
    int killNum = 0;
    while (leftNum != totalNum-killNum)
    {
      int count = 1;
      while (count != deathNum)//找到本次要被杀的人
      {
        temp = temp->next;
        ++count;
      }
      ++killNum;
      temp = killSomeone(temp,killNum);//杀掉此人
    }
    return true;
  }
  ```
  
  其中，杀掉某个特定乘客的函数killSomeone实现为
  
  ```c++
  Passenger* Circle::killSomeone(Passenger* passenger, int killNum)
  {
    Passenger* temp = passenger->next;
    passenger->front->next = temp;
    temp->front = passenger->front;

    if (passenger == head)//防止删除节点时丢失头结点
      head = temp;

    cout << "第" << killNum << "个死者位置是：\t" << passenger->getID() << endl;
    delete(passenger);
    passenger = NULL;

    return temp;//返回被杀的人下一个位置上的人
  }
  ```
  注意，killSomeone函数负责将被杀死的乘客的节点丛链表上删除，并释放内存。除此之外还要打印杀掉的乘客信息，并且返回指向下一个乘客的指针。
  
- #### 展示生还乘客  
  
  根据循环链表的特性，由头指针所指向的节点开始，遍历链表，打印信息，直到回到头指针指向的节点  

  ```c++
  void Circle::showAll()
  {
    Passenger* temp = head;
    cout << endl;
    cout << "最后剩下：\t" << leftNum << "人" << endl;
    if (leftNum != 0)
    {
      cout << "剩余的生者位置为：\t" << temp->getID();
      temp = temp->next;

      while (temp != head)//检查是否回到起点
      {
        cout << '\t' << temp->getID();
        temp = temp->next;
      }
      cout << endl;
    }
  }
  ```
  
### 5. 容错测试
  
- #### 输入错误的总人数  

  输入小于等于0的总人数时，会被要求重新输入  

  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q2/image/totalNumError.PNG)
  
- #### 输入错误的开始位置  

  1. 输入小于等于0的开始位置，会默认为从第一名乘客开始计算  
  2. 输入大于总人数的开始位置，会进行重复环绕匹配，即开始位置=开始位置%总人数  

  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q2/image/startNumError.PNG)  

  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q2/image/startNumError2.PNG)
  
- #### 输入错误的死亡数字

  输入小于等于0、大于总人数的死亡数字，会被要求重新输入  

  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q2/image/deathNumError.PNG)
  
- #### 输入错误的生还者数字

  属于小于等于0、大于总人数的生还者数字，会被要求重新输入  

  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q2/image/leftNumError.PNG)
