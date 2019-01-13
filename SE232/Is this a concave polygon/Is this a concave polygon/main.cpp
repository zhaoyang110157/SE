//
//  main.cpp
//  Is this a concave polygon
//
//  Created by 朱朝阳 on 2018/9/19.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//点顺时针输入

#include<iostream>
#include <cmath>
#include <vector>
using namespace std;
bool isconcave(vector<double> x,vector<double>y,int n);
int isvalid(vector<double> x,vector<double>y,int i,int n);
int notsameside(vector<double> x,vector<double>y,int a,int b,int c,int d);
int main(){
	int n;//用来确定输入的数目
	vector<double> x;
	vector<double> y;
	cout<<"Please give me the number and points. If you show me 0, then the program will shut down."<<endl;
	while(cin>>n){
		if(n==0){
			break;
		}
		bool* fool=new bool[n+2];//fool为真时，这是个凸点
		for(int i=1;i<=n;i++){
			int a,b;
			cin>>a>>b;
			x.push_back(a);
			y.push_back(b);
		}
		if(n==1||n==2){
			cout<<"concave"<<endl;
			continue;
		}

		int num=0;
		for(int i=0;i<n;i++){
			if((x[(i+1)%n]-x[i])*(y[(i+2)%n]-y[(i+1)%n])-(x[(i+2)%n]-x[(i+1)%n])*(y[(i+1)%n]-y[i])<0){
				num++;
				fool[(i+1)%n]=true;
			}else  fool[(i+1)%n]=false;
		}
		if(num==n||num==-n){
			cout<<"convex"<<endl;
		}
		else {
			cout<<"concave"<<endl;
			//既然是凹多边形就开始分割
			for(int i=1;i<=n;i++)
				if(fool[i]){//只要找到第一个凸点，就可以开始切割。
					if(isvalid(x,y,i,n)){
					cout<<"开始切割"<<i<<endl;
					cout<<x[i-1]<<","<<y[i-1]<<" "<<x[(i)%n]<<","<<y[i%n]<<" "<<x[(i+1)%n]<<","<<y[(i+1)%n]<<endl;
					x.erase(x.begin()+i%n);
					y.erase(y.begin()+i%n);
					if(isconcave(x, y,n-1))
					break;
				}
			}
		}
		cout<<"task finished"<<endl;
		delete[] fool;
		cout<<"Please reput"<<endl;
	}
	return 0;
}
bool isconcave(vector<double> x,vector<double>y,int n){
	cout<<"the num of the left points"<<n<<endl;
	if(n==3){ cout<<x[0]<<","<<y[0]<<" "<<x[1]<<","<<y[1]<<" "<<x[2]<<","<<y[2]<<endl;return true;}
	bool* fool=new bool[n+2];
	int num=0;
	for(int i=0;i<n;i++){
		if(((x[(i+1)%n]-x[i])*(y[(i+2)%n]-y[(i+1)%n])-(x[(i+2)%n]-x[(i+1)%n])*(y[(i+1)%n]-y[i]))<0){
			num++;
			fool[(i+1)%n]=true;
		}else  {fool[(i+1)%n]=false;}
	}
	if(num==n){
		for(int i=1;i<=n-1;i++)
		cout<<x[i]<<","<<y[i]<<" ";
		cout<<x[0]<<","<<y[0]<<endl;
		return true;
	}
	else {
		//既然是凹多边形就开始分割
		for(int i=1;i<n+1;i++)
		{
			if(fool[i%n])
			{//只要找到第一个凸点，就可以开始切割。
				if(isvalid(x,y,i,n)!=0)
				{
					if(isvalid(x,y,i,n)==1)
					{
						cout<<x[i-1]<<","<<y[i-1]<<" "<<x[i%n]<<","<<y[i%n]<<" "<<x[(i+1)%n]<<","<<y[(i+1)%n]<<endl;
					}
					x.erase(x.begin()+i%n);
					y.erase(y.begin()+i%n);
					isconcave(x, y,n-1);
					break;
					
				}
			}
		}
	}
	delete[] fool;
	return true;
};
int isvalid(vector<double> x,vector<double>y,int i,int n){
	for(int j=0;j<n-3;j++)
	{
		int a=notsameside(x, y, i-1, i, i+1,(i+2+j)%n);
		int b=notsameside(x, y, i, i+1, i-1,(i+2+j)%n);
		int c=notsameside(x, y, i-1, i+1, i,(i+2+j)%n);
		
		if((a+b+c)==0)
		return 0;
		if(a+b+c==6)return 2;
	}
		return 1;
};
int notsameside(vector<double> x,vector<double>y,int a,int b,int c,int d){
	if(x[a]!=x[b])
	{
		int k=(y[a]-y[b])/(x[a]-x[b]);
		int g=y[a]-k*x[a];
		if((y[c]-k*x[c]-g)==0)return 2;
		if((y[c]-k*x[c]-g)*(y[d]-k*x[d]-g)>=0)
			return 0;//同侧或者共线
		else 	return 1;//异侧
	}
	else {
		if(x[c]==x[a]) return 2;
		if((x[c]-x[a])*(x[d]-x[a])>=0)
			return 0;
		else 	return 1;
		
	}
		
};

/*
11
0 3
3 3
3 2
5 4
5 2
4 2
4 1
5 1
6 5
6 1
3 0
*/
/*#include<iostream>
 #include <cmath>
 using namespace std;
 double eps = 1e-10;
 int main(){
 int n;//用来确定输入的数目
 int loc=0;//用来记录奇异点位
 cout<<"Please give me the number and points. If you show me 0, then the program will shut down."<<endl;
 while(cin>>n){
 if(n==0){
 break;
 }
 double* x=new double[n+3];
 double* y=new double[n+3];
 double* strange=new double[n+1];//凹进去点的位置
 for(int i=1;i<=n;i++){
 cin>>x[i]>>y[i];
 }
 if(n==1||n==2){
 cout<<"concave"<<endl;
 continue;
 }
 x[n+1]=x[1];
 y[n+1]=y[1];
 x[n+2]=x[2];
 y[n+2]=y[2];
 int num=0;
 for(int i=1;i<=n;i++){
 if((x[i+1]-x[i])*(y[i+2]-y[i+1])-(x[i+2]-x[i+1])*(y[i+1]-y[i])<0){
 num++;
 }else  {strange[loc]=i+1;loc++;}
 //此处因为顺时针输入，则全部为负,则正的就是凹下去的点
 if((x[i+1]-x[i])*(y[i+2]-y[i+1])-(x[i+2]-x[i+1])*(y[i+1]-y[i])>0){
 num++;
 }else if((x[i+1]-x[i])*(y[i+2]-y[i+1])-(y[i+1]-y[i])*(x[i+2]-x[i+1])<0){
 num--;
 }//如果为凸，将全部为正或者为负。
}
if(num==n||num==-n){
	cout<<"convex"<<endl;
	}
	else {
		cout<<"concave"<<endl;
		//既然是凹多边形就开始分割
		
	}
	loc=0;
	delete[] x;
	delete[] y;
	}
	return 0;
	}*/
