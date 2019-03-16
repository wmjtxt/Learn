 ///
 /// @file    :test1.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-13 10:38:33
 /// @quote   :
 ///
 
#include <iostream>
#include "Stringcpp.h"
using namespace std;

int main(){
	String a = String("1234");
    String b("456");
    String c = b;
    cout << a << endl;
    cout << b << endl;
    cout << &a << endl;
    cout << &b << endl;
    b = a;
    cout << a << endl;
    cout << b << endl;
    cout << &a << endl;
    cout << &b << endl;
    cout << a.size() << endl;
    cout << b.size() << endl;
	return 0;
}
