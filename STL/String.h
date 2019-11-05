 ///
 /// @file    :String.h
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-02 13:45:29
 /// @quote   :
 ///

#ifndef __STRING_H__
#define __STRING_H__

#include <stdio.h>
#include <cstring>
#include <iostream>

using std::ostream;
using std::cout;
using std::endl;
using std::size_t;


class String{
public:
    explicit //必须显示转换
    String(const char* str = "");
    //String(const String s);
    String(const String & str);//复制构造
    String(const int n, const char c);
    String& operator=(const String &str);
    String& operator+=(const String &str);
    int size();
    friend ostream& operator<<(ostream& os, const String& s);
    ~String();

private:
    char *_str;
    size_t  _size;
    size_t capacity;
};
ostream& operator<<(ostream& os, const String &s);


//difination

String::String(const char* str)
{
    cout << "构造函数String(const char*)" << endl;
    if(!strcmp(str,""))
    {
        _str = new char[1];
        _size = 0;
    }
    else{
        _str = new char[strlen(str)+1];
        _size = strlen(str);
        strcpy(_str, str);
    }
}


String::String(const String & str)
: _str(new char[str._size + 1])
, _size(str._size)
{
    cout << "拷贝构造函数String(const String&)" << endl;
    strcpy(_str, str._str);
}


String::String(const int n, const char c)
: _str(new char[n+1])
, _size(n)
{
    cout << "构造函数String(const int,const char)" << endl;
    int i = 0;
    while(i<n) _str[i++] = c;
}

String& String::operator=(const String& s)
{
    cout << "拷贝赋值运输符operator=" << endl;
    if(this == &s)
        return *this;
    delete [] _str;
    _str = new char[strlen(s._str)+1];
    _size = strlen(s._str);
    strcpy(_str, s._str);
    return *this;
}

String& String::operator+=(const String& s)
{
    cout << "复合赋值运输符operator+=" << endl;
    char* tmp = new char[_size + s._size + 1];
    strcpy(tmp,_str);
    strcat(tmp,s._str);
    delete [] _str;
    _size += s._size;
    //strcpy(_str,tmp);
    _str = tmp;
    return *this;
}

int String::size(){
    return _size;
}

String::~String(){
    delete [] _str;
    cout << "析构函数" << endl;
}

//friend ostream& operator<<(ostream& os, String &s);

ostream& operator<<(ostream& os, const String &s){
    os << s._str;
    return os;
}

#endif

