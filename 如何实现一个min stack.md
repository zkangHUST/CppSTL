# 如何实现一个min stack
Q: 如何设计一个特殊的栈,支持min()操作,返回栈中的最小元素.

这个问题来源于去年面试遇到的一道题目,面试官给了20分钟时间让设计这样一个栈.当时时间有限,虽然写出来了一个版本,但是那个版本还存在很多的问题,比如不够通用,只能支持`int`类型数据;同时,效率也不高, 存在大量的数据拷贝.

面试完后又仔细思考了一下,重新写了一个版本,记录一下,分享给大家！这个版本主要解决前面说的两个问题,1.通用性;2.效率.

## 1. 接口设计

既然要解决通用性的问题,让这个栈支持所有的数据类型,必须使用`template`.

同时,为了支持`min()`操作,我们需要两个数组.数组a保存push到栈中的数据,数组b记录最小值,数组a每做一次更新(push或者pop),数组b都要随之更新.

再仔细想一下,数组b真的需要保存最小值吗?其实在数组a中已经有了最小值得一份拷贝,在b数组中再存一次会造成空间浪费,而且如果存储在栈中的是一个非常庞大的类类型,把该类型数据写入b数组也是相当耗时的.这样就造成了空间和时间上的双重浪费,显然这是不合理的.事实上,在b数组中完全没有必要存储实际的类对象,只要存储一下该对象在a数组中的索引就可以了,这样既节省空间,又提高了速度.

基于上面的分析,我们可以设计下面的接口.

```c++
template <class T>
class stack
{
private:
  // 栈的top指针
  int   top;           
  // 最小值top指针
  int   minTop;        
  T     buf[1024]; 
  // 记录最小值索引             
  int   minIndex[1024];
  const int  maxsize = 1024;
public:
  int push(const T& item);
  T   pop();
  //更新最小值索引
  int pushMinIndex(const T& item);
  int popMinIndex();
  T   min(); // 返回最小值
  stack();
  stack(const stack& s);
  stack& operator=(const stack& s);
  ~stack();
};
```

## 2.接口实现

基于上面的设计,我们可以轻松写出代码来.
```C++
#ifndef MY_STACK_H
#define MY_STACK_H
#include<cassert>
#define ERROR -1
#define OK   0
template <class T>
class stack
{
private:
  int     top;
  int     minTop;
  T       buf[1024];
  int     minIndex[1024];
  const int   maxsize = 1024;
public:
  int push(const T& item);
  int pushMinIndex(const T& item);
  int popMinIndex();
  T   min();
  T   pop();
  stack();
  stack(const stack& s);
  stack& operator=(const stack& s);
  ~stack();
};

template<class T>
stack<T>::stack():top(-1), minTop(-1) 
{

}

template<class T>
stack<T>::~stack() {}

template<class T>
int stack<T>::push(const T& item)
{
  top++;
  if ((top >= maxsize) || (top < 0)) {
    return ERROR;
  }
  buf[top] = item;
  pushMinIndex(item);
  return OK;
}

template<class T>
T stack<T>::pop() 
{
  assert(top >= 0);
  popMinIndex();
  return buf[top--];
}

// 关键函数,保存最小值索引
template<class T> 
int stack<T>::pushMinIndex(const T& item)
{
  minTop++;
  if ((minTop >= maxsize) || (minTop < 0)) {
    return ERROR;
  }
  if (minTop == 0) {
    minIndex[minTop] = top;
    return OK;
  }
  if (item < buf[minIndex[minTop - 1]]) {
    minIndex[minTop] = top;
  } else {
    minIndex[minTop] = minIndex[minTop - 1];
  }
  return OK;
}

template<class T>
int stack<T>::popMinIndex()
{
  minTop--;
  return OK;
}

template<class T>
T stack<T>::min()
{
  assert(minTop >= 0);
  return buf[minIndex[minTop]];
}

// 拷贝构造函数和赋值运算符重载,标配
template<class T>
stack<T>::stack(const stack<T>& s):top(s.top), minTop(s.minTop)
{
  top = s.top;
  minTop = s.minTop;
  for (int i = 0; i <= top; i++) {
    buf[i] = s.buf[i];
  }
  for (int i = 0; i <= minTop; i++) {
    minIndex[i] = s.minIndex[i];
  }
}

template<class T>
stack<T>& stack<T>::operator=(const stack<T>& s)
{
  top = s.top;
  minTop = s.minTop;
  for (int i = 0; i <= top; i++) {
    buf[i] = s.buf[i];
  }
  for (int i = 0; i <= minTop; i++) {
    minIndex[i] = s.minIndex[i];
  }
  return *this;
}
#endif
```

## 3. 测试一下

我们写一个小例子测试一下自己写的stack是否好用.

```C++
#include <iostream>
#include "minstack.hpp"
using namespace std;
int main()
{
  stack<double> s;
  double a[] = {8.1, 7.2, 9.5, 6.3, 2.5, 5.6, 3.5};
  for (int i = 0; i < 7; i++) {
    s.push(a[i]);
    cout << s.min() << " ";
  }
  cout << endl;
  stack<double> t;
  t = s;
  cout << "---------------------------" << endl;
  for (int i = 0; i < 7; i++) {
    cout << t.min() << " ";
    t.pop();
  }
  return 0;
}
```
编译一下
```
g++ -g main.cpp -Wall
```
运行结果
```
$ ./a.out
8.1 7.2 7.2 6.3 2.5 2.5 2.5
---------------------------
2.5 2.5 2.5 6.3 7.2 7.2 8.1
```
看起来没什么问题哦~
代码已上传至github，链接在此
https://github.com/zkangHUST/CppSTL

THE END.
