 ///
 /// @file    :huawei2.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-20 20:29:01(NewYork time)
 /// @quote   :
 ///
 

#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

int main(){
    string s;
    cin >> s;
    int n = s.size();
    vector<char> v(256,0);
    for(auto e : s){
        if(isalpha(e)){
            ++v[e];
        }
    }
    //cout << 'A'-'a' << endl;
    //for(auto e : v)
    //    if(e != 0)
    //        cout << e << endl;
    string ret = "";
    while(1){
        //cout << "while" << endl;
        ret = "";
        for(int i = 0; i < v.size(); ++i){
            if(i+32 < v.size() && v[i] != 0 && v[i+32] != 0){
                //cout << (char)i << (char)(i+32) << endl;
                while(i+32 < v.size() && v[i] != 0 && v[i+32] != 0){
                    ret = ret + (char)(i) + (char)(i+32);
                    --v[i];
                    --v[i+32];
                    ++i;
                }
                cout << ret << endl;
                //ret = "";
                break;
            }
        }
        if(ret == "") break;
    }
    return 0;
}
