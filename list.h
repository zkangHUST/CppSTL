#ifndef LIST_H
#define LIST_H
#include<iostream>
using namespace std;
template<typename T> 
class List{
public:
    struct item {
        T value;
        item* next;
    };
    class Iterator;
    List();
    ~List();
    Iterator begin();
    Iterator end();
    // Iterator begin();
    // Iterator 
    void push_back(const T& it);
    void push_front(const T& it);
    void travel();

private:
    item head;
    item* tail;
    int size;
};
#endif

template<typename T> 
List<T>::List()
{
    head.next = nullptr;
    tail = &head;
    size = 0;
    cout << "list construct" << endl;
}

template<typename T> 
List<T>::~List()
{
    item* p = head.next;
    item* q = p->next;
    while(p) {
        delete p;
        p = q;
        if (q) {
            q = q->next;
        }
    }
}

template<typename T> 
void List<T>::push_back(const T& it)
{
    item *p = new item;
    p->value = it;
    tail->next = p;
    p->next = nullptr;
    tail = p;
    size++;
}

template<typename T> 
void List<T>::push_front(const T& it)
{
    item *p = new item;
    p->value = it;
    p->next = head.next;
    head.next = p;
    size++;
}

template<typename T> 
void List<T>::travel()
{
    item *p ;
    p = head.next;
    while (p) {
        cout << p->value << " " ;
        p = p->next;
    }
}

template<typename T> 
typename List<T>::Iterator List<T>::begin()
{
    typename List<T>::Iterator it(this->head.next);
    return it;
}


template<typename T> 
typename List<T>::Iterator List<T>::end()
{
    typename List<T>::Iterator it(tail->next);
    return it;
}


template<typename T>
class List<T>::Iterator {
public:
    Iterator();
    Iterator(item* it);
    item& operator*();
    item* operator->();
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==(const Iterator& it);
    bool operator!=(const Iterator& it);
private:
    item* p;

};

template<typename T>
List<T>::Iterator::Iterator()
{
    p = nullptr;
}

template<typename T>
List<T>::Iterator::Iterator(item* it):p(it)
{

}

template<typename T>
typename List<T>::item& List<T>::Iterator::operator*()
{
    return *p;
}

template<typename T>
typename List<T>::item* List<T>::Iterator::operator->()
{
    return p;
}

// 前置
template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
    p = p->next;
    return *this;
}

// 后置
template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
    Iterator it = *this;
    p = p->next;
    return it;
}

template<typename T>
bool List<T>::Iterator::operator==(const Iterator& it)
{
    return p == it.p;
}

template<typename T>
bool List<T>::Iterator::operator!=(const Iterator& it)
{
    return p != it.p;
}


