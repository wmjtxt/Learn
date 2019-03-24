 ///
 /// @file    :huawei1.cpp
 /// @author  :wmjtxt(972213032@qq.com)
 /// @date    :2019-03-20 20:58:25(NewYork time)
 /// @quote   :
 ///
 
#include <stdio.h>
//#include <conio.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
    string exp;
    //char exp[1000000];
    //getline(cin,exp,'=');
    char c;
    //read(1,&c,1);
    //while(c != '='){
    //    exp += c;
    //    read(1,&c,1);
    //}
    //cin >> exp;
    //cin >> c;
    //int j = 0;
    
    while((c = getchar()) != '='){
        exp += c;
        //exp[j] = c;
        //++j;
    }
    int sum = 0;
    int tmp = 0;
    int flag = 0;
    for(int i = 0; i < exp.size(); ++i){
        if(exp[i] == '+'){
            if(flag == 0) sum += tmp;
            else sum -= tmp;
            flag = 0;
            tmp = 0;
        }else if(exp[i] == '-'){
            if(flag == 0) sum += tmp;
            else sum -= tmp;
            flag = 1;
            tmp = 0;
        }else{
            tmp = tmp*10 + exp[i] - '0';
        }
    }
    if(flag == 0) sum += tmp;
        else sum -= tmp;
    cout << sum << endl;
    return 0;
}
