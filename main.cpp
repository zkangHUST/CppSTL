#include <iostream>
<<<<<<< HEAD
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
=======
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
>>>>>>> 1b4e55dde410aab7dfcb0529ed937c7e071f3263
}