 ///
 /// @file    :test.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-02 10:58:40
 /// @quote   :
 ///
 
#include <iostream>
using namespace std;

int main(){
	//double dval = 3.14;
    //const int &ri = dval;
    //cout << ri << endl;

    //int i = 42;
    //const int &r1 = i;
    //cout << r1 << endl;
    //i = 40;
    //cout << r1 << endl;

    int i = 42;
    int j = 12;
    int *const p1 = &i;
    int ci = 42;
    const int *p2 = &ci;
    const int *const p3 = p2;
    const int &r = ci;
    *p1 = 39;
    cout << "i = " << i << endl;
    cout << "*p1 = " << *p1 << endl;
    //p1 = &j;
    //*p2 = 40;
    cout << "*p3 = " << *p3 << endl;
    ci = 4;
    cout << "*p3 = " << *p3 << endl;
    cout << "ci = " << ci << endl;
    cout << "*p2 = " << *p2 << endl;
    p2 = &j;
    cout << "*p2 = " << *p2 << endl;
	return 0;
}
