 ///
 /// @file    :String.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-13 09:56:21
 /// @quote   :
 ///
 
#ifndef __STRINGCPP_H__
#define __STRINGCPP_H__

#include "String.h" 

String::String(const char* str)
{
    if(str == "")
    {
        _str = new char[1];
        _size = 0;
    }
    else{
        cout << "构造函数String(const char*)" << endl;
        _str = new char[strlen(str)+1];
        _size = strlen(str);
        strcpy(_str, str);
    }
}

String::String(const String & str)
: _str(new char[strlen(str._str) + 1])
, _size(strlen(str._str))
{
    cout << "构造函数String(const String&)" << endl;
    strcpy(_str, str._str);
}

String::String(const int n, const char c)
: _str(new char[n+1])
, _size(n)
{
    int i = 0;
    cout << "构造函数String(const int,const char)" << endl;
    while(i<n) _str[i++] = c;
}

String& String::operator=(String s)
{
    cout << "operator=" << endl;
    if(this == &s)
        return *this;
    delete [] _str;
    _str = new char[strlen(s._str)+1];
    _size = strlen(s._str);
    strcpy(_str, s._str);
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

ostream& operator<<(ostream& os, String &s){
    os << s._str;
    return os;
}


//int main(){
//	String s;
//    String h("hello");
//    String hh = "world";
//    String str = h;
//    cout << str << endl;
//    str = hh;
//    cout << str << endl;
//    cout << str.size() << endl;
//    cout << s.size() << endl;
//    String s4(10,'c');
//    cout << s4 << endl;
//	return 0;
//}

#endif
