# MyADT

数据结构及算法分析学习工程，使用 Visual Studio 开发。

数据结构是一门研究程序设计问题中计算机的操作对象以及它们之间的关系和操作的学科。

# 术语

## 数据（data）

对客观事物的符号表示，在计算机科学中是指所有能输入到计算机中并被计算机程序处理的符号的总称。

## 数据元素（data element）

数据的基本单位，在计算机程序中通常作为一个整体进行考虑和处理。

## 数据项（data item）

数据项是数据不可分割的最小单位，一个数据元素可由若干个数据项组成。

## 数据对象（data object）

性质相同的数据元素的集合，是数据的一个子集。

## 抽象数据类型（abstract data type, ADT）

一个数学模型以及定义在该模型上的一组操作。使用如下格式进行定义：
```
ADT 抽象数据类型名 {
    数据对象: <数据对象的定义>
    数据关系: <数据关系的定义>
    基本操作: <基本操作的定义>
} ADT 抽象数据类型名
```

其中，数据对象和数据关系的定义用伪码描述，基本操作的定义格式为：
```
基本操作名(参数表)
    初始条件: <初始条件描述>
    操作结果: <操作结果描述>
```

每个 ADT 都需要明确三方面的内容：
1. 定义，这个 ADT 是什么？
2. 表示，这个 ADT 该怎么存储（顺序存储、链式存储...）？
3. 实现，这个 ADT 如何用代码实现（不同的表示可能导致不同的实现）？

## 算法

对特定问题求解步骤的一种描述，是指令的有限序列，其中每一条指令表示一个或多个操作。

## 算法时间复杂度

算法时间复杂度记作：`T(n) = O(f(n))`，表示随着问题规模 n 的增大，算法执行时间的<font color="red">增长率</font>和算法中基本操作重复执行的次数的<font color="red">增长率</font>相同。

在分析基本操作重复执行次数时，可以得到 f(n) 是关于 n 的一个多项式，比如：f(n) = kn + c 等。

我们将多项式中 n 增长最快的那一项，比如 kn，去掉常数系数 k 后，作为 f(n) 的一个替代，得到 O(n)，即为算法的时间复杂度。

因此，如果要分析一个算法的时间复杂度，需要先找出算法中的基本操作，然后再列出基本操作关于规模 n 的多项式，最终得出时间复杂度。

同时，需要注意的是，计算时间复杂度时，计算的是最坏情况下的时间复杂度。

## 算法空间复杂度

算法空间复杂度记作：`S(n) = O(f(n))`，表示随着问题规模 n 的增大，算法占用内存空间大小的变化。

算法的空间复杂度通常就是两种：O(1) 和 O(n)，其中涉及递归的算法是 O(n)，其余的是 O(1)。

计算空间复杂度时，同样是考虑最坏情况。