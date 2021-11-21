// Copyright 2021  Tian Tan tiant@bu.edu

/*
int类型的范围很小，解决不了特别大的数字

该版本有问题，通不过checker文件。原因是会溢出，即使用double或者long long/long double
类型也没有用，超长位数时，无法得出正确结果 
 
*/ 
#include <string>
#include <vector>
#include "bigint.h"
#include <iostream>

using std::cout;
typedef std::string BigInt;

BigInt multiply_int( const BigInt &a, const BigInt &b) {
    int lena;
    int lenb;
    lena = a.size();
    lenb = b.size();
    std::vector<int>num1;
    std::vector<int>num2;

    int digit;
    int temp;

    int base1 = 1;
    int t1 =0;
    for (int i=lena-1; i>=0; i--) {
        digit = a.at(i) - '0'; 
        temp = digit*base1;
        num1.push_back(temp);
        base1 = 10*base1;
        cout << num1.at(t1) << " ";
        t1+=1;
    }
    cout << "\n";

    int base2 = 1;
    int t2 =0;
    for (int j=lenb-1; j>=0; j--) {
        digit = b.at(j) - '0'; 
        temp = digit*base2;
        num2.push_back(temp);
        base2 = 10*base2;
        cout << num2.at(t2) << " ";
        t2+=1;
    }
    cout<<"\n";

    int result=0;//要及时赋初值，不然会报错 
    for (int i=0; i<lena; i++){
        for (int j=0; j<lenb; j++) {
            result += num1.at(i)*num2.at(j);
            cout << result<<" ";
        }
    }
    cout<<(num1.at(0)*num2.at(0))<<"\n";

    BigInt output;
    BigInt numstr;
    numstr = std::to_string(result);
    int len = numstr.size();
    for (int r=0; r<len; r++) {
        temp = numstr.at(r);
        output.push_back(temp);
    }
    return output;

}
