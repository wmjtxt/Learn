 ///
 /// @file    :test2.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-29 18:07:02
 /// @quote   :
 ///
 
#include <iostream>
#include "String.h"
using namespace std;

int main(){
	String dots(10, '.');
    String s(dots);
    String s2 = dots;
    String null_book = "9-99-999";
    String nines = String(100, '9');
    String s3("hello");
    String s4;
    s4 = s3;
    cout << dots << endl;
    cout << s << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
    cout << null_book << endl;
    cout << nines << endl;
	return 0;
}
