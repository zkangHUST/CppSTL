#include "mystring.h"
#include<cstring>
#include<cstdlib>
#include<cassert>
myString::myString()
{   
    size = 1;
    p = new char[size + 1];
    p[0] = '\0';
    len = 0;
}

myString::myString(const char *s)
{
    size = 1;
    len = strlen(s);
    if (len > max_size) {
        len = max_size;
    }
    while (size < len) {
        size *= 2;
    }
    p = new char[size + 1];
    strncpy(p, s, size);
    p[size] = '\0';
}
myString::myString(const myString& s) 
{
    size = s.size;
    p = new char[size + 1];
    strcpy(p, s.p);
    len = s.len;
}
myString::myString(char c, int length):len(length)
{
    size = 1;
    if (len > max_size) {
        len = max_size;
    }
    while(size < len) {
        size *= 2;
    }
    p = new char[size + 1];
    memset(p, c, len);
    p[size] = '\0';
}

myString::~myString()
{
    delete[] p;
}
ostream& operator<< (ostream& out, const myString& s)
{
    out << s.p ;
    return out;
}
istream& operator>> (istream& in, myString& s)
{
    cout << "call >> " << endl; 
    char buf[s.max_size + 1];
    in.getline(buf, s.max_size + 1);
    s.len = strlen(buf);
    if (s.len > s.max_size) {
        s.len = s.max_size;
    }
    if (s.size >= s.len) {
        strcpy(s.p, buf);
    } else {
        while(s.size < s.len) {
            s.size *= 2;
        }
        char *tmp = new char[s.size + 1];
        strcpy(tmp, buf);
        delete[] s.p;
        s.p = tmp;
    }
    return in;
}
// 重载+=运算符
myString& myString::operator+= (const char* s)
{
    len += strlen(s);
    len = len > max_size ? max_size : len;
    if (size > len) {
        strncat(p, s, size - strlen(p));
        p[size] = '\0';
        return *this;
    }
    while (size < len) {
        size *= 2;
    }
    char *tmp = new char[size + 1];
    strncpy(tmp, p, strlen(p));
    tmp[strlen(p)] = '\0';
    strncat(tmp, s, size - strlen(p));
    tmp[size] = '\0';
    delete[] p;
    p = tmp;
    return *this;
}

myString& myString::operator+= (const myString& s)
{
    len += s.len;
    len = len > max_size ? max_size : len;
    if (size > len) {
        strncat(p, s.p, size - strlen(p));
        p[size] = '\0';
        return *this;
    }
    while (size < len) {
        size *= 2;
    }
    char *tmp = new char[size + 1];
    strncpy(tmp, p, strlen(p));
    tmp[strlen(p)] = '\0';
    strncat(tmp, s.p, size - strlen(p));
    tmp[size] = '\0';
    delete[] p;
    p = tmp;
    return *this;
}
// 重载赋值运算符
myString& myString::operator= (const myString& s)
{
    if (&s == this) {
        return *this;
    }
    delete[] p;
    size = s.size;
    p = new char[size + 1];
    strncpy(p, s.p, s.len);
    p[s.len] = '\0';
    len = s.len;
    return *this;
}
char myString::operator[] (const int index)
{
    // 确保索引没有越界
    assert(index >=0  && index < len);
    return p[index]; 
}
const char& myString::operator[] (const int index) const      // 为了给const对象使用，只能访问，不能改写
{
    assert(index >=0  && index < len);
    return p[index]; 
}
// append实现
myString& myString::append(const myString& str)
{
    len += str.len;
    if (size >= len) {
        strcat(p, str.p);

    } else {
        if (len > max_size) {
            len = max_size;
        }
        while(size < len) {
            size *= 2;
        }
        char *tmp = new char[size + 1];
        strcpy(tmp, p);
        strncat(tmp, str.p, size - strlen(tmp));
        delete[] p;
        p = tmp;
    }
}
myString& myString::append (const char* s)
{
    len += strlen(s);
    if (len <= size) {
        strcat(p, s);
    } else {
        if (len > max_size) {
            len = max_size;
        }
        while (size < len) {
            size *= 2;
        }
        char *tmp = new char[size + 1];
        strcpy(tmp, p);
        strncat(tmp, s, size - strlen(tmp));
        delete[] p;
        p = tmp;
    }
}
void myString::clear()
{
    p[0] = '\0';
    len = 0;
}
bool myString::empty()
{
    if(len == 0) {
        return true;
    }
    return false;
}
myString myString::operator+(const myString& s)
{
    myString res(*this);
    res.len += s.len;
    if (res.len > max_size) {
        res.len = max_size;
    }
    if (res.size >= res.len) {
        strncat(res.p, s.p, res.size - strlen(this->p));
        res.p[size] = '\0';
        return res;
    } 
    while(res.size < res.len) {
        res.size *= 2;
    }
    char *tmp = new char[res.size + 1];
    strncpy(tmp, this->p, strlen(this->p));
    tmp[strlen(this->p)] = '\0';
    strncat(tmp, s.p, res.size - strlen(this->p));
    tmp[res.size] = '\0';
    delete[] res.p;
    res.p = tmp;
    return res;
}
myString myString::operator+(const char* s)
{
    myString res(*this);
    res.len += strlen(s);
    if (res.len > max_size) {
        res.len = max_size;
    }
    if (res.size >= res.len) {
        strncat(res.p, s, res.size - len);
        res.p[size] = '\0';
        return res;
    } 
    while(res.size < res.len) {
        res.size *= 2;
    }
    char *tmp = new char[res.size + 1];
    strncpy(tmp, this->p, strlen(this->p));
    tmp[strlen(this->p)] = '\0';
    strncat(tmp, s, res.size - strlen(this->p));
    tmp[res.size] = '\0';
    delete[] res.p;
    res.p = tmp;
    return res;
}