/*
积的位数为两个因子位数之和 
*/ 


#include "bigint.h"
#include <iostream>
#include <string>
#include <vector> 
using namespace std;
using std::stoi;


BigInt multi(string a, string b) {
	// initialize parameters
	int lena;// a: 1234 -> len=4, power=3
	int lenb;

	lena = a.size();
	lenb = b.size();
	int len=lena+lenb;
	vector<int>output(len,0);// create a vector whose size is 'size', and all elements are 0
	
	//检查异常输入：0，负数。下面的for循环，如果输入有0，则不输出。不知道原因；知道了，如下：
	//输入0，输出0的原因是后面去掉高位多余的0代码的原因。
	//如果输入有负数，则会按ascii码计算，得出一个带字符的结果 
	//最后判断0的情况即可，没有必要开头去判断输入的a,b是否为0，
	//直接判断结果就行，结果全为0，则输出0，不全为0，则正常操作 
	
	//正着遍历不太清楚最终结果矩阵的power对应的是多少 
	//其实可以知道power的，与索引有关系，可以算出power 
	int digit=0;
	int remainder=0;
	int powera,powerb;
	int lexp,hexp;
	int index=0;//迭代次数，也就是power 
	
	for (int i=lena-1; i>=0; i--) {
		powera = lena-1-i;
		
		for (int j=lenb-1; j>=0; j--) {
			powerb = lenb-1-j;
			digit = (a.at(i)-'0') * (b.at(j)-'0');
			index = powera+powerb;//这两项相乘以后得到数，其本身对应的幂次 
			
			//需要进位 
			if (digit>=10) {
//				digit = digit/10;
//				remainder = digit%10;
				/*
				上面两行代码产生了特别大的问题，造成bug。
				你将digit更新了以后再来求remainder,就不对了！！
				要么就先求remainder，要么就不要重复命名 
				*/
				remainder = digit%10;
				digit = digit/10;
				
				//低位，即其本身对应的幂次
				lexp = output.at(index);//该幂次下本身存的系数
				output.at(index) = lexp+remainder;   
				cout<<lexp<<" "<<output.at(index)<<"\n"; 
				//高位(高一个幂次),一次肯定只进一位 
				hexp = output.at(index+1); 
				output.at(index+1) = hexp+digit;  
				cout<<hexp<<" "<<output.at(index+1)<<"\n"; 
			}
			//不需要进位 
			else {
				lexp = output.at(index);
				output.at(index) = lexp+digit;
			}
			/*
			有两种情况会进位，一个是两项相乘时结果大于10；
			还一种是，乘积不大于10，但是加上该幂次下已有的系数值后大于10
			这两种有一个好处：若进位，始终都只可能进一位 
			*/
			
			//检查同幂次下系数相加后，进位情况 
			//if (output.at(index)) 
			//感觉最后再一个for循环检查整个output比较好 
			
		}
	}
	cout<<output.at(0)<<"\n";
	//同幂次下系数相加大于10的问题 
	for (int t=0; t<len; t++) {
		if (output.at(t)>=10){
			digit =  output.at(t) / 10;
			remainder = output.at(t) % 10;
			output.at(t) = remainder;
			hexp = output.at(t+1);
			output.at(t+1) = hexp + digit;//更新高一位的值 
		}
	} 
	
	//检查最终结果的位数。去掉高位多余的0，这一步要放在最后，需
	//要先处理上面说的，同幂次下系数相加大于10的问题 
	int num0 = 0; // the number of redundant zero
	for (int w=len-1; w>=0; w--) {
	if (output.at(w)==0) {
		num0 = num0+1;	
	}
	else
		break;//一旦检测到非零的值，就跳出循环 
	}
	cout<<output.at(0)<<" "<< num0<<"\n";
	
	//最后一步，将结果反转，且输出为string
	string result;
	int size = len-num0;
	//int temp;
	char temp;
	//cout<<size<<"\n";
    //int love = 0;
    if (size==0){//检查乘积结果为0的情况.size=0,说明乘积的结果全都是0 
    	result = '0';
	}
	else{
		for (int m=size-1; m>=0; m--) {
			//temp = output.at(m);
			temp = output.at(m)+'0'; // convert to char
			cout<<temp<<" ";
			/*
			出现了bug，一切正常，但是给result赋值不成功。
			我觉得原因应该是，output向量里的元素是int类型，不能直接赋值
			给string类型 
			结果：
			我的猜想是对的，虽然编译可以通过，但是如果将Int元素赋值给string
			将赋值不成功。将temp改为char类型，并且output.at(m)+'0';变成字符 
			*/
			result.push_back(temp);
			//cout<<"This"<<result.at(love)<<" ";
	        //love = love+1;
		}
	}
	
	//cout<<result;
	return result;
	
}


int main() {
	BigInt A, B;

  	std::cin >> A >> B;

  	std::cout << multi(A, B) << std::endl;
	
	//c = (a.at(3)-'0')*(b.at(1)-'0');
	//因为c本身是Int型，所以即使不加Int强制转换，也会变为ascii计算后的int数字 
	//int 强制转换一个char是变成其ASCII码，并不是char表面代表的数字 
	//stoi是将一个字符串变为其表面代表的数字，比如string a = '1234'
	// int c = stoi(a); c=1234，然后可以用1234做数学运算，但是stoi不能只转换一个字符
	// stoi(a.at(2));会报错 
	
	//所以这里我觉得只能用ascii码来解决。反正输入时十进制数，以为着，数的每一位只能是0-9之间 
	
	//c = multi(a,b);

	
	//result = stoi(c);
	//cout << a.at(3)<<" "<<b.at(1) << " "<<c<< "\n"; 
	
}



