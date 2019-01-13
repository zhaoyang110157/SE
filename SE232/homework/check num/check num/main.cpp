//
//  main.cpp
//  check num
//
//  Created by 朱朝阳 on 2018/9/15.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//

#include <iostream>
using namespace std;
int main(int argc, const char * argv[]) {
	int num;
	cin>>num;
	int *array=new int[num];
	for(int j=0;j<num;j++)cin>>array[j];
	for(int i=0;i<num;i++)
	{
		bool flag=false;
		for(int j=i+1;j<num;j++)
			if(array[i]==array[j])
			{
				for(int t=j;t<num-1;t++)
					array[t]=array[t+1];
				num--;
				j--;
				flag=true;
			}
		if(flag) {for(int t=i;t<num-1;t++)
			array[t]=array[t+1];
			num--;i--;}
	}
	cout<<array[0];
	return 0;
}
