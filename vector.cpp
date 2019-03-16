 ///
 /// @file    :vector.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-02 15:46:24
 /// @quote   :
 ///
 
#include <iostream>
#include <vector>
using namespace std;

int main(){
	vector<string> svec(10,"hi");
	vector<string> svec1{10,"hi"};
    for(auto i : svec) cout << i << " ";
    cout << endl;
    for(auto i : svec1) cout << i << " ";
    vector<int> v;
    int a;
    while(cin >> a){
        v.push_back(a);
    }
    for(auto i : v) cout << i << " ";
    cout << endl;
	return 0;

}
