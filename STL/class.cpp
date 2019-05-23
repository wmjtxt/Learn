 ///
 /// @file    :class.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-04-03 10:29:16
 /// @quote   :
 ///
 
#include "String.h"
#include <iostream>
using namespace std;

class A{};

class B{
    string s;
};

class C{
    String s;
};
int main(){
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;
	return 0;
}
