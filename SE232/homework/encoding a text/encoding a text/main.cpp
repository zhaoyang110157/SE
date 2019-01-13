//
//  main.cpp
//  encoding a text
//
//  Created by 朱朝阳 on 2018/10/14.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;
int main(int argc, const char * argv[]) {
	char temp;
	char input[101]={};
	char all[101]={};
	int add=0,count=0;
	
	cin.getline(input, 101,EOF);
	while(count<=100){
		temp=input[count];
		if((temp>='0'&&temp<='9')||(temp>='a'&&temp<='z')||(temp>='A'&&temp<='Z'))
		{
			if(temp>='A'&&temp<='Z')
				temp-='A'-'a';
			all[add]=temp;
			add++;
		}
		count++;
	}
	if(add){
		int a=ceil(sqrt(add));
		int b=floor(sqrt(add));
		
		if(a*b<add)
			b++;

			for(int i=0;i<a;i++)
				for(int j=0;j<b;j++)
					if(i+j*a<add)	std::cout<<all[i+j*a];
					else  cout<<" ";
	}
	else std::cout<<"Null";
	return 0;
}
