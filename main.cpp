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