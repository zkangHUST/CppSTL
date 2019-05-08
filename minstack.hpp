#ifndef MY_STACK_H
#define MY_STACK_H
#include<cassert>
#define ERROR -1
#define OK     0
template <class T>
class stack
{
private:
    int         top;
    int         minTop;
    T           buf[1024];
    int         minIndex[1024];
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