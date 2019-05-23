 ///
 /// @file    :test.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-02 14:04:08
 /// @quote   :
 ///
 
#include <iostream>
#include "String.h"
using namespace std;

void test1(){
	String s;
    String h("hello");
    String hh = "world";
    String str = h;
    cout << str << endl;
    str = hh;
    cout << str << endl;
    cout << str.size() << endl;
    cout << s.size() << endl;
    String s4(10,'c');
    cout << s4 << endl;
    hh = hh;
}

void test2(){
    String s1 = "hello";
    cout << "-" << endl;
    String s2;
    s2 = "world";
    cout << &s1 << endl;
    s1 += s2;
    s1 += ".";
    s1 += '.';
    cout << &s1 << endl;
    cout << s1 << endl;
}

int main(){
    test2();
	return 0;
}
