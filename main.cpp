#include <iostream>
#include "myvector.h"
#include<string>
using namespace std;
int main()
{
    int c = 20;
    Vector<string> a;
    Vector<string> b;
    for (int i = 0 ; i < 3; i++) {
        a.push_back("hello");
    }
    b = a;
    for (Vector<string>::iterator it = b.begin(); it != b.end(); it++) {
        cout << *it << " " << endl;
    }
    return 0;
}