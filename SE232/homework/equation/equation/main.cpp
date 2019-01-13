//
//  main.cpp
//  equation
//
//  Created by 朱朝阳 on 2018/10/21.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include<ctime>
using namespace std;

bool  calculate(double a,double b,vector<double> c);
double cal(double a,double b,int type, bool& q);
string num2str(double i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}

int target;
vector<string> output;//used for debug
string mark="+--*//";

int main(int argc, const char * argv[]) {
	int count(0);//used to count the num of solution
	vector<double> input;
	int ncount;

	
	cin >> ncount >> target;
	
	for(int i = 0 ; i < ncount ; i++)
	{
		int temp;
		cin >> temp;
		input.push_back(temp);//get input nums
	}
	
		float time_begin=clock();
	if( ncount > 1)
	{
		for(int i = 0 ; i < ncount && count==0 ; i++)
		for(int j = i + 1 ; j < ncount && count==0; j++)
			if (calculate( i, j, input))	count++;
	}
	else 	if( input[0] == target ) 	count++;
	
	for(int i = 0; i < output.size(); i++)
		cout<<output[i]<<endl;
	
	if(count) cout<<"True"; else cout<<"False";
	
	cout<<endl<<(clock()-time_begin)/1000;
	
	return 0;
}
bool  calculate(double a,double b,vector<double> c)
{
	int x = c[a] , y = c[b];
	int i;
	for(i = 0 ; i < 6 ; i++)
	{
		
		bool trial=false;//trial is used to prevent 0 divided
		double temp=cal(x, y, i, trial);// calculate x and y
		if(trial) continue;
		else{//the following is valid operation
			vector<double> now=c;
			output.push_back(num2str(x)+mark[i]+num2str(y));// store this step
			now[a]=temp; now.erase(b+now.begin());
		
			
				bool succeed=false;
				if(now.size()!=2)
				for(int j = 0; j < now.size() && succeed==false; j++)
					for(int k = j+1; k < now.size() && succeed==false; k++)
						succeed = calculate(j ,k ,now);
				else {
					succeed=((now[0]+now[1])==target)||((now[0]-now[1])==target)||((-now[0]+now[1])==target)||((now[0]*now[1])==target)||((now[0]/now[1])==target)||((now[1]/now[1])==target);
				}
				if(succeed) break;
				else output.pop_back();
					
		}
	}
	if( i < 6 ) return true;
	//if found, then the succeed should be true. So the circulation is stopped in advance
	else	return false;
	//c is a copied vector here
}

double cal(double a,double b, int type,bool& q )
{
	switch (type) {
		case 0:
			return a+b;
		case 1:
			return a-b;
		case 2:
			return b-a;
		case 3:
			return a*b;
		case 4:
		{
			if(a==0) {
				q=true;//report virus
				return 0;
			}
			else return b/a;
		}
		default:
		{
			if(b==0) {
				q=true;//report virus
				return 0;
			}
			else return a/b;
		}
	}
}
