 ///
 /// @file    :string.h
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


class String{
public:
    explicit String(const char* str = "");
    String(const String & str);
    String(const int n, const char c);
    String& operator=(String str);
    int size();
    friend ostream& operator<<(ostream& os, String& s);
    ~String();

private:
    char *_str;
    int  _size;
};

#endif
