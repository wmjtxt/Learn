 ///
 /// @file    :prac243.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-02 11:49:22
 /// @quote   :
 ///
 
#include <iostream>
using namespace std;

int main(){
	
    const int v2 = 0;
    int i = 0, v1 = v2;
    int *p1 = &v1, &r1 = v1;
    const int *p2 = &v2, *const p3 = &i, &r2 = v2;
    int *const p4 = &i;

    r1 = v2;
    //p1 = p2;
    p2 = p1;
    //p1 = p3;
    p2 = p3;
    p1 = p4;
    cout << *p3 << endl;
    i = 2;
    cout << *p3 << endl;
	return 0;
}
