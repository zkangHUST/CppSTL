#include<iostream>
using std::cout;
using std::endl;

template<class T> 
struct __list_node {
    __list_node() {}
    __list_node(const T& val):data(val) {}
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};  

template<class T, class Ref, class Ptr>
struct __list_iterator {
    typedef __list_iterator<T, Ref, Ptr> self;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref  reference;
    typedef __list_node<T>* link_type;

    link_type node;

    __list_iterator(link_type x): node(x) {}
    __list_iterator() {}

    reference operator*() const { return (*node).data;};
    pointer operator->() const {return &(operator*());}
    self& operator++() {
        node = (link_type)((*node).next);
        return *this;
    }

    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(const self& x) const {return node == x.node;}
    bool operator!=(const self& x) const {return node != x.node;}

};

template<class T>
class list {
protected:
    typedef __list_node<T> list_node;
public:
    typedef list_node* link_type;
    typedef __list_iterator<T, T&, T*> iterator;
protected:
    link_type node;
public:
    list(); 
    ~list();
    iterator insert(iterator position, const T& val);
    iterator begin();
    iterator end();
    void push_front(const T& val);
    void push_back(const T& val);
    iterator erase(iterator position);
    void clear();
    bool empty();
};

template<class T> 
list<T>::list() {
    node = new list_node();
    node->next = node;
    node->prev = node;
}

template<class T> 
list<T>::~list() {
    clear();
    delete node;
}


template<class T>
typename list<T>::iterator list<T>::insert(iterator position, const T& val)
{   
    link_type tmp = new list_node(val);
    tmp->next = position.node;
    tmp->prev = position.node->prev;
    (link_type(position.node->prev))->next = tmp;
    position.node->prev = tmp;
    return tmp;
}

template<class T>
typename list<T>::iterator list<T>::begin()
{
    return (link_type)((*node).next);
}

template<class T>
typename list<T>::iterator list<T>::end()
{
    return node;
}

template<class T>
void list<T>::push_front(const T& val)
{
    insert(this->begin(), val);
}

template<class T>
void list<T>::push_back(const T& val)
{
    insert(this->end(), val);
}

template<class T>
typename list<T>::iterator list<T>::erase(iterator position)
{
    link_type tmp = (link_type)position.node->next;
    (link_type(position.node->prev))->next = position.node->next;
    (link_type(position.node->next))->prev = position.node->prev;
    delete position.node;
    return tmp;
}

template<class T>
void list<T>::clear() 
{
    link_type p = (link_type)node->next;
    while (p != node) {
        link_type q = (link_type)p->next;
        delete p;
        p = q;
    }
    node->next = node;
    node->prev = node;
}

template<class T>
bool list<T>::empty()
{
    if (node.next == node) {
        return true;
    }
    return false;
}