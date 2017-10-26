# 数据结构课程设计

#### 作者：张文喆

## 考试报名系统项目说明文档

### 0. 项目简介  
考试报名工作给各高校报名工作带来了新的挑战，给教务管理部门增加了很大的工作量。
本项目是对考试报名管理的简单模拟，用控制台选项的选择方式完成下列功能：
输入考 生信息；输出考生信息；查询考生信息；添加考生信息；修改考生信息；删除考生信息。 
 
### 1. 项目运行效果  

- 建立数据库  

  说明：程序一旦开始运行，便会要求建立数据库，并要求输入数据库的初始大小。  
  键入数据库大小后，程序便会根据数据库的大小要求输入考生信息。该要求会一直打印，直到输入了足够的数据。  
  输入的数据要求每项之间用任意个空格隔开。

![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q1/build.PNG)

- 插入考生信息  

  说明：键入1，便会进入插入信息分支，程序会要求输入插入的考生的信息。  
  输入的数据要求每项之间用任意个空格隔开。

![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q1/insert.PNG)

- 删除考生信息

  说明：键入2，便会进入删除信息分支，程序会要求输入删除的考生的考号。

![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q1/delete.PNG)

- 查找考生信息 

  说明：键入3，便会进入查找信息分支，程序会要求输入查找的考生的考号，并返回找到的信息。

![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q1/find.PNG)

- 修改考生信息

  说明：键入4，便会进入修改信息分支，程序会要求输入修改后的考生的信息。  
  输入的数据要求用任意个空格隔开，并且考生的考号无法修改，必须找到相同的考号才能修改。

![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q1/fix.PNG)

- 统计考生信息

  说明：键入5，便会进入统计信息分支，程序会打印整个数据库。

![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q1/showall.PNG)


### 2. 概述  
- #### 项目要求及建议  
  本项目的实质是完成对考生信息的建立，查找，插入，修改，删除等功能。
  其中考生信息包括准考证号，姓名，性别，年龄和报考类别等信息。
  项目在设计时应首先确定系统的数据结构，定义类的成员变量和成员函数；
  然后实现各成员函数以完成对数据操作的相应功能； 
  最后完成主函数以验证各个成员函数的功能并得到运行结果。（建议采用链表实现）

- #### 实现方法  
  本项目采用了双向链表建立数据库（由`Database`类实现），每一个节点（由`Student`类实现）记录考生报名信息。  
  注：链表中没有专门的头结点和尾结点。

### 3. 类及类成员介绍  
- #### Student类  
  - ###### 成员变量  
  |成员名称 |属性|类型|描述|
  |--------|----|---|----|
  |front|public|Student*|指向上一个考生的指针|
  |next|public|Student*|指向下一个考生的指针|
  |num|private|string|记录考生考号|
  |name|private|string|记录考生姓名|
  |sex|private|string|记录考生性别|
  |age|private|string|记录考生年龄|
  |job|private|string|记录考生报名岗位|
  
  - ###### 成员函数
  |函数名称|返回值类型|描述|
  |-------|---------|----|
  |Student|无|构造函数|
  |getInfo|string|返回考生信息|
  |getNum|string|返回考生考号|
  |changeName|void|修改考生姓名|
  |changeSex|void|修改考生性别|
  |changeAge|void|修改考生年龄|
  |changeJob|void|修改考生报名岗位|
  
- #### Database类
  - ###### 成员变量
  |成员名称 |属性|类型|描述|
  |--------|----|---|----|
  |head|private|Student*|指向Student对象组成的链表的头指针|
  |numOfData|private|int|记录数据库中考生数量|
  
  - ###### 成员函数
  |函数名称|返回值类型|描述|
  |-------|---------|----|
  |Database|无|构造函数|
  |~Database|无|析构函数，清空数据库中数据，释放内存|
  |getHead|Student*|返回头指针|
  |insert|bool|插入新的考生数据，插入成功返回true|
  |find|Student*|查找考生，返回指向该考生节点的指针，失败返回NULL|
  |deleteStu|bool|删除考生节点，删除成功返回true|
  |fix|bool|修改考生信息，修改成功返回true|
  |showAll|void|打印数据库中所有考生信息|
  
### 4. 容错测试

- #### 建立数据库时输入错误的考生人数大小  

  输入小于0的考生人数，一律视为0
  
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q1/buildError.PNG)
  
- #### 插入时输入错误的位置  

  输入小于1的位置，一律视为1  
  输入大于链表长度的位置，一律插在链表末尾
  
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q1/insertError.PNG)
  
- #### 试图删除不存在的考生  

  打印提示信息：“查无此人！”
  
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q1/deleteError.PNG)
  
- #### 试图查找不存在的考生  

  打印提示信息：“查无此人！”
  
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q1/findError.PNG)
  
- #### 试图修改不存在的考生  

  打印提示信息：“查无此人！”
  
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q1/fixError.PNG)
 
