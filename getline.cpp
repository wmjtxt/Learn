 ///
 /// @file    :getline.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-02 15:09:58
 /// @quote   :
 ///
 
#include <iostream>
using namespace std;

int main(){
    int n = 9;
	string s;
    //cin >> n;
    getchar();
    getline(cin, s);
    cout << "n = " << n << "\ns = " << s << endl;
	return 0;
}
