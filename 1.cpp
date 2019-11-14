#include "list.hpp"
#include<iostream>
using namespace std;

int main()
{
    
    list<int> a;
    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }

    for (list<int>::iterator it = a.begin(); it != a.end(); it++) {
        cout << *it << endl;
    }
    list<int>::iterator it = a.begin();
    it++;
    a.erase(it);
    for (list<int>::iterator it = a.begin(); it != a.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}