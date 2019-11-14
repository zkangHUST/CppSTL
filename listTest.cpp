#include "list.h"
#include<iostream>
#include<string>
using namespace std;
int main()
{
    List<string> a;
    a.push_back("I");
    a.push_back("Love");
    a.push_back("Erli");
    a.travel();
    // List<string>::Iterator it = a.begin();
    for (List<string>::Iterator it = a.begin(); it != a.end(); it++) {
        cout << it->value << endl;
    }
    // cout << it->value << endl;
    return 0;
}