//
//  main.cpp
//  cut the cake
//
//  Created by 朱朝阳 on 2018/11/15.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int Split(const string& src,const string& separator, vector<int>& dest)
{
	string str = src;
	int tmp;
	int max=0;
	string::size_type start = 0, index;
	dest.clear();
	index = str.find_first_of(separator,start);
	do
	{
		if (index != string::npos)
		{
			tmp = atoi(str.substr(start,index-start ).c_str());
			if(tmp>max) max=tmp;
			dest.push_back(tmp);
			start =index+separator.size();
			index = str.find(separator,start);
			if (start == string::npos) break;
		}
	}while(index != string::npos);
	
	//the last part
	tmp = atoi(str.substr(start ).c_str());
	if(tmp>max) max=tmp;
	dest.push_back(tmp);
	return max;
}
int main(int argc, const char * argv[]) {
	int max;
	int output = 0;
	int num=0;
	vector< int >  input;
	vector< int >  temp;
	string str;
	getline(cin,str);
	max=Split(str,",",input);
	
	while (max>0 && input.size()>0 )
	{
		for(int i=0 ; i<input.size() ; i++)
		{
			if(input[i] == max)
			{
				temp.push_back(i);
				input[i]--;
			}
		}
		for(int i=0 ; i<temp.size()-1; i++ )
		{
			int tmp=0;
			while(i<temp.size()-1){
				if(temp[i]+1 == temp[i+1])
				{
					i++;
					tmp++;
				}
				else {
					break;
				}
			}
			
			if(tmp>num) num=tmp;
		}
		num++;
		output=(output>num*max)?output:num*max;
		num=0;
		temp.clear();
		max--;
	}
	cout<<output;
	return 0;
}
