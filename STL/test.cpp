 ///
 /// @file    :test.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-02 14:04:08
 /// @quote   :
 ///
 
#include <iostream>
#include "Stringcpp.h"
using namespace std;

int main(){
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
	return 0;
}
