#ifndef MY_STRING_H
#define MY_STRING_H
#include<iostream>
using namespace std;
class myString {
public:
    myString();
    myString(const char* s);
    myString(const myString&);
    myString(char c, int length);
    myString& operator= (const myString& s);
    // []下标运算符重载
    char operator[] (const int index);
    const char& operator[] (const int index) const;
    // +=重载
    myString& operator+= (const char* s);
    myString& operator+= (const myString& s);
    // 加号重载
    myString operator+(const myString& s);
    myString operator+(const char* s);
    // append 函数实现
    myString& append(const myString& str);
    myString& append (const char* s);
    void clear();
    bool empty();
    // << 重载
    friend ostream& operator<< (ostream& out, const myString& s);
    // >> 
    friend istream& operator>> (istream& in, myString& s);
    inline int length() const;
    inline int capacity() const;
    inline const int max_length() const;
    ~myString();
private:
    char        *p;
    int         len;
    int         size;
    const int   max_size = 65536;
};
inline int myString::length() const
{
    return len;
}
inline int myString::capacity() const
{
    return size;
}
inline const int myString::max_length() const
{
    return max_size;
}
#endif