# 数据结构课程设计

#### 作者：张文喆

## 勇闯迷宫游戏

### 0. 项目简介  
迷宫只有两个门，一个门叫入口，另一个门叫出口。  
一个骑士骑马从入口进入迷宫，迷宫设置很多障碍，骑士需要在迷宫中寻找通路以到达出口。 

### 1. 项目运行效果

- 建立迷宫地图

  迷宫地图是通过内建的构造函数自动生成的，无需输入。  
  由于题目没有指明如何输入地图信息，所以程序中使用了默认信息，如果想要更改地图，需要  
  ```c++
  Field::Field()
	:row(7), column(7), isAccess(true)
  ```
  在这里改变地图的长度和宽度（此处长度和宽度都为7）  
  并且需要
  ```c++
  field[1][1] = field[2][1] = field[3][1] = field[3][2] = field[3][3] = field[2][5]
		= field[4][1] = field[5][1] = field[1][3] = field[2][3] = field[5][3] = field[1][4]
		= field[1][5] = field[4][3] = field[4][4] = field[3][5] = field[4][5] = field[5][5] = SPACE;
  ```
  在这里具体指明哪些点是通路
  
- 骑士寻找出口

  由生成的Knight类对象执行内建的findWay函数寻路，并使用drawSolutionOnMap将路径在地图上标记出来。  
  由于没有提供修改地图的接口，所以骑士的入口和出口也无法通过外部指定，但是可以
  ```c++
  auto knight = new Knight(1, 1, 5, 5);
  ```
  在这里指明入口（前两个参数）和出口（后两个参数），每组参数的含义为（横坐标，纵坐标）。  
  
- 展示结果

  展示结果分为两步  
  - 展示地图
  ```c++
  field->showMap();
  ```
  - 展示路径
  ```c++
  knight->showAll();
  ```
  值得注意的是，如果这个迷宫没有通路，那么不会展示路径，取而代之的士打印一条“没有通路！”的语句。
  
- 运行截屏

  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q3/image/run1.PNG)
  
  （与题目演示中的运行结果一致） 
  
### 2. 概述

- #### 项目要求及建议

  迷宫问题的求解过程可以采用回溯法即在一定的约束条件下试探地搜索前进，若前进中受阻，则及时回头纠正错误另择通路继续搜索的方法。  
  从入口出发，按某一方向向前探索，若能走通，即某处可达，则到达新点，否则探索下一个方向；若所有的方向均没有通路，则沿原路返回前一点，换下一个方向再继续试探，直到所有可能的道路都探索到，或找到一条通路，或无路可走又返回入口点。  
  在求解过程中，为了保证在达到某一个点后不能向前继续行走时，能正确返回前一个以便从下一个方向向前试探，则需要在试探过程中保存所能够达到的每个点的下标以及该点前进的方向，当找到出口时试探过程就结束了。  
  
- #### 实现方法

  回溯法的实现方法有很多，最简单的是使用递归。因为每完成一次递归，都会回到上一层递归所处的状态（要求函数参数传参数而非传值或者传引用），所以可以自然而然地完成任务  
  如果不使用递归，可以使用栈保留经过的路径点，利用栈“后进先出”的特性，每当栈顶的点被证实不通时，就将它弹出。如此操作，直到找到通路或成为空栈（无通路）  
  这里，我使用的是栈，栈中每个节点记录路径点的坐标和四个方向是否已经走过，并且为了便于操作，还包含指向前后元素的指针。  
  栈的节点由Point类进行描述，它的头指针保存在Knight类的对象中。  
  
### 3. 类及类成员介绍  

- #### Field类
  
  - ##### 成员变量
  |成员名称 |属性|类型|描述|
  |--------|----|---|----|
  |field|public|int**|指向迷宫（二维数组）起始位置的指针|
  |isAccess|public|bool|标记迷宫是否用通路|
  |row|private|int|迷宫数组的行数|
  |column|private|int|迷宫数组的列数|
  
  - ##### 成员函数
  |函数名称|返回值类型|描述|
  |-------|---------|----|
  |Field|无|构造函数|
  |~Field|无|析构函数，释放掉迷宫数组占用的内存|
  |canAccess|bool|检测一点是否为通路（空地）|
  |showMap|void|打印地图|
  
- #### Point类
  
  - ##### 成员变量
  |成员名称|属性|类型|描述|
  |-------|----|----|----|
  |positionX|public|int|记录点的横坐标|
  |positionY|public|int|记录点的纵坐标|
  |next|public|Point*|指向下一个节点|
  |front|public|Point*|指向上一个节点|

  - ##### 成员函数
  |函数名称|返回值类型|描述|
  |--------|---------|---|
  |Point|无|构造函数|
  |linkNext|Point*|链接下一个指针，并返回指向其的指针|
  
- #### Knight类

  - ##### 成员变量
  |成员名称|属性|类型|描述|
  |--------|---|---|----|
  |head|private|Point*|栈顶指针|
  |canReachEnd|private|bool|描述骑士能否到达终点|
  |endX|private|int|终点的横坐标|
  |endY|private|int|终点的纵坐标|
  
  - ##### 成员函数
  |函数名称|返回值类型|描述|
  |-------|----------|---|
  |Knight|无|构造函数|
  |~Knight|无|析构函数，释放栈占用的内存|
  |findWay|bool|寻路函数，成功返回true，失败返回false|
  |drawSolutionOnMap|void|将结果路径标记在迷宫数组上|
  |showAll|void|保存栈中保存的路径|

### 4. 核心代码解释

  - #### 建立迷宫地图  
  
  ```c++
  #define BLOCK 0
  #define SPACE 1
  #define TESTED 2
  #define SOLUTION 3
  ```
  0代表不通的点（如墙壁），1代表通的点（空地），2代表次点已经被测试过，3代表次点位于最终结果的路径上  

  ```c++
  Field::Field()
	:row(7), column(7), isAccess(true)
  {
    field = new int *[row];
    ...

    for (int i = 0; i < row; ++i)
    {
      field[i] = new int[column];
      ...
    }

    for (int i = 0; i < row; ++i)
      for (int j = 0; j < column; ++j)
        field[i][j] = BLOCK;

    field[1][1] = field[2][1] = field[3][1] = field[3][2] = field[3][3] = field[2][5]
      = field[4][1] = field[5][1] = field[1][3] = field[2][3] = field[5][3] = field[1][4]
      = field[1][5] = field[4][3] = field[4][4] = field[3][5] = field[4][5] = field[5][5] = SPACE;
  }
  ```
  由此可见，初始化迷宫的顺序是先将所有点置为0，再将部分点置为1  

  - 链接下一个节点  

  将新的Point对象压入栈时，需要考虑两种情况，首先是原先的栈顶元素还没有链接过其他点，再是原先的栈顶元素曾经链接过其他点，但由于那个点不在最终结果的通路上，所以被抛出了栈（回溯）。  
  于是我们需要验证这一点，并且按照设计的逻辑，被抛出栈的节点的释放也要在这里完成。  

  ```c++
  Point* Point::linkNext(int x, int y)
  {
    if (this->next != NULL)//删掉原有的节点
      delete(this->next);

    Point* temp = new Point(x, y);
    ...
    temp->front = this;
    this->next = temp;
    return temp;
  }
  ```
  在这里我们做一个测试，以决定是否有一个被抛出栈的元素，如果有，就删掉它。然后建立新的元素并且压入栈，最后返回指向那个被压入栈的新元素的指针，也即栈顶指针。  
  
  - 寻路
  
  整个寻路的过程都是回溯的过程，我们要借助迷宫地图数组上的标记（如标记为2的测试过的点就不应该再作为新的测试点，因为它们已经被证明了是不会到达终点的）来完成它。  
  
  ```c++
  bool Knight::findWay(Field* field)
  {
    Point* temp = head;
    while (temp->positionX != endX || temp->positionY != endY)
    {
      field->field[temp->positionX][temp->positionY] = TESTED;//防止走回头路，使走过的路不可再走
      if (field->canAccess(temp->positionX - 1, temp->positionY))//向上走
        temp = temp->linkNext(temp->positionX - 1, temp->positionY);
      else if (field->canAccess(temp->positionX, temp->positionY - 1))//向左走
        temp = temp->linkNext(temp->positionX, temp->positionY - 1);
      else if (field->canAccess(temp->positionX, temp->positionY + 1))//向右走
        temp = temp->linkNext(temp->positionX, temp->positionY + 1);
      else if (field->canAccess(temp->positionX + 1, temp->positionY))//向下走
        temp = temp->linkNext(temp->positionX + 1, temp->positionY);
      else//无路可走，即没有通路
      {
        temp = temp->front;//回到链表中上一个节点处

        if (temp == NULL)//链表中已无可选择的路径，即无路可走
        {
          field->isAccess = false;//宣告迷宫无通路
          canReachEnd = false;//宣告骑士无法走出迷宫
          return false;
        }
      }

      ...
    }
    return true;
  }
  ```
  我知道这看起来似乎很复杂，但是它是很容易分析和理解的——它只是看上去很长而已。  
  首先我们要明白，整个函数只被执行一次（因为它是非递归的），所以我们是从栈为空的前提下进行链接的，所以我们从栈的底部（head）开始。  
  接着的while循环直到找到通向终点的通路才会正常终止，但是它也必须要具备一旦发现没有通路就终止循环的能力。  
  循环中的一大片判断是为了逐个方向地验证邻近的点是否为通路（曾被测试过的点不能算作通路）。如果是的话，就将这个点压入栈，并更新指针，进行新的循环。  
  最后，当我们无路可走时，就说明栈顶元素代表的节点不在最终通路上，我们要将它抛出，这样就可以回溯到它的上一个节点处了。但是如果栈已经空了，说明我们已经回到起点了，并且起点也没有其他的可以尝试的方向了，也就是说，这个迷宫是没有通路的。这个时候我们就可以跳出，并且将一些标记迷宫是否有通路的布尔值标为false。  
  
### 5. 容错测试

由于本项目不支持外部输入，所以要求测试时应保持迷宫数组大小的合理性，并且只有`SPACE`（宏）会被视为通路。  

- #### 含有圈的测试

  在这种情况下，迷宫中含有圈，而寻路时不应该在圈中陷入死循环。为了保证我们的骑士确实走入到圈中了，我特地调整了findWay中的判断顺序。  
  
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q3/image/run2.PNG)
  
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q3/image/run2Sign.jpg)
  
- #### 没有通路情况下的测试

  在这种情况下，骑士不应当陷入死循环，而且打印时也要求一些变化。  
  
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q3/image/run3.PNG)
  
  ![image](https://github.com/pancerZH/dataStructureProject/blob/master/Q3/image/run3Sign.jpg)
