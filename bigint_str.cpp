/*
����λ��Ϊ��������λ��֮�� 
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
	
	//����쳣���룺0�������������forѭ�������������0�����������֪��ԭ��֪���ˣ����£�
	//����0�����0��ԭ���Ǻ���ȥ����λ�����0�����ԭ��
	//��������и�������ᰴascii����㣬�ó�һ�����ַ��Ľ�� 
	//����ж�0��������ɣ�û�б�Ҫ��ͷȥ�ж������a,b�Ƿ�Ϊ0��
	//ֱ���жϽ�����У����ȫΪ0�������0����ȫΪ0������������ 
	
	//���ű�����̫������ս�������power��Ӧ���Ƕ��� 
	//��ʵ����֪��power�ģ��������й�ϵ���������power 
	int digit=0;
	int remainder=0;
	int powera,powerb;
	int lexp,hexp;
	int index=0;//����������Ҳ����power 
	
	for (int i=lena-1; i>=0; i--) {
		powera = lena-1-i;
		
		for (int j=lenb-1; j>=0; j--) {
			powerb = lenb-1-j;
			digit = (a.at(i)-'0') * (b.at(j)-'0');
			index = powera+powerb;//����������Ժ�õ������䱾���Ӧ���ݴ� 
			
			//��Ҫ��λ 
			if (digit>=10) {
//				digit = digit/10;
//				remainder = digit%10;
				/*
				�������д���������ر������⣬���bug��
				�㽫digit�������Ժ�������remainder,�Ͳ����ˣ���
				Ҫô������remainder��Ҫô�Ͳ�Ҫ�ظ����� 
				*/
				remainder = digit%10;
				digit = digit/10;
				
				//��λ�����䱾���Ӧ���ݴ�
				lexp = output.at(index);//���ݴ��±�����ϵ��
				output.at(index) = lexp+remainder;   
				cout<<lexp<<" "<<output.at(index)<<"\n"; 
				//��λ(��һ���ݴ�),һ�ο϶�ֻ��һλ 
				hexp = output.at(index+1); 
				output.at(index+1) = hexp+digit;  
				cout<<hexp<<" "<<output.at(index+1)<<"\n"; 
			}
			//����Ҫ��λ 
			else {
				lexp = output.at(index);
				output.at(index) = lexp+digit;
			}
			/*
			������������λ��һ�����������ʱ�������10��
			��һ���ǣ��˻�������10�����Ǽ��ϸ��ݴ������е�ϵ��ֵ�����10
			��������һ���ô�������λ��ʼ�ն�ֻ���ܽ�һλ 
			*/
			
			//���ͬ�ݴ���ϵ����Ӻ󣬽�λ��� 
			//if (output.at(index)) 
			//�о������һ��forѭ���������output�ȽϺ� 
			
		}
	}
	cout<<output.at(0)<<"\n";
	//ͬ�ݴ���ϵ����Ӵ���10������ 
	for (int t=0; t<len; t++) {
		if (output.at(t)>=10){
			digit =  output.at(t) / 10;
			remainder = output.at(t) % 10;
			output.at(t) = remainder;
			hexp = output.at(t+1);
			output.at(t+1) = hexp + digit;//���¸�һλ��ֵ 
		}
	} 
	
	//������ս����λ����ȥ����λ�����0����һ��Ҫ���������
	//Ҫ�ȴ�������˵�ģ�ͬ�ݴ���ϵ����Ӵ���10������ 
	int num0 = 0; // the number of redundant zero
	for (int w=len-1; w>=0; w--) {
	if (output.at(w)==0) {
		num0 = num0+1;	
	}
	else
		break;//һ����⵽�����ֵ��������ѭ�� 
	}
	cout<<output.at(0)<<" "<< num0<<"\n";
	
	//���һ�����������ת�������Ϊstring
	string result;
	int size = len-num0;
	//int temp;
	char temp;
	//cout<<size<<"\n";
    //int love = 0;
    if (size==0){//���˻����Ϊ0�����.size=0,˵���˻��Ľ��ȫ����0 
    	result = '0';
	}
	else{
		for (int m=size-1; m>=0; m--) {
			//temp = output.at(m);
			temp = output.at(m)+'0'; // convert to char
			cout<<temp<<" ";
			/*
			������bug��һ�����������Ǹ�result��ֵ���ɹ���
			�Ҿ���ԭ��Ӧ���ǣ�output�������Ԫ����int���ͣ�����ֱ�Ӹ�ֵ
			��string���� 
			�����
			�ҵĲ����ǶԵģ���Ȼ�������ͨ�������������IntԪ�ظ�ֵ��string
			����ֵ���ɹ�����temp��Ϊchar���ͣ�����output.at(m)+'0';����ַ� 
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
	//��Ϊc������Int�ͣ����Լ�ʹ����Intǿ��ת����Ҳ���Ϊascii������int���� 
	//int ǿ��ת��һ��char�Ǳ����ASCII�룬������char������������ 
	//stoi�ǽ�һ���ַ�����Ϊ������������֣�����string a = '1234'
	// int c = stoi(a); c=1234��Ȼ�������1234����ѧ���㣬����stoi����ֻת��һ���ַ�
	// stoi(a.at(2));�ᱨ�� 
	
	//���������Ҿ���ֻ����ascii�����������������ʱʮ����������Ϊ�ţ�����ÿһλֻ����0-9֮�� 
	
	//c = multi(a,b);

	
	//result = stoi(c);
	//cout << a.at(3)<<" "<<b.at(1) << " "<<c<< "\n"; 
	
}



