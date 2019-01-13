//
//  main.cpp
//  the longest distence between to prime number
//
//  Created by 朱朝阳 on 2018/9/21.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;
int main(){
	unsigned long long M,N;
	cin>>M>>N;
	if(N==0||N==1||N==2) {
		cout<<"0";
		return 0;
	}
	if(M<2)M=2;
	unsigned long long len=sqrt(N)+1;
	bool prime[155537]={1,1};
	bool pri[1000001]={};
	for(int i=2;i<len;i++){
		if (prime[i])
			continue;
		for (int j = 2 * i; j <= len; j += i)
		{
			prime[j]=1;
		}
		for(unsigned long long j=ceil(M/i)*i;j<N+1;j+=i)
			{
				pri[j-M] = true;
			}
	}
	unsigned long long front=0,distence=0;
	bool first=true,second=false;
	for(unsigned long long i=N;i>=M;i--)
	{
		if(!pri[i-M])
		{
			if(first)
			{
				front=i;
				first=false;
			}
				else
			{
				second=true;
				unsigned long dis=(front-i);
				if(dis>distence)
					distence=dis;
				front=i;
			}
		}
	}
	if(!second)cout<<"0";
	else cout<<distence;
	return 0;
}
/*某种高深算法
 #include<iostream>
 #include<cstdio>
 #include<cmath>
 #include<cstring>
 #include<algorithm>
 using namespace std;
 const int maxn=50005;
 const int maxnum=1000005;
 bool pri[maxn];   //pri[i]=true表示i是素数
 int primes[maxn];//primes[i]表示50000以内第i个素数
 bool s[maxnum];  //s[i-a]=true表示i是合数
 int k=1;
 void solve1()  //筛选出50000以内的素数
 {
 memset(pri,true,sizeof pri);
 for(int i=2;i<maxn;i++)
 {
 if(pri[i])
 {
 primes[k++]=i;
 for(int j=i+i;j<maxn;j+=i)
 pri[j]=false;
 }
 }
 }
 void solve2(int a,int b)//筛出a到b以内的合数
 {
 for(int i=1;i<k;i++)
 {
 int p=(a-1)/primes[i]+1;
 int q=b/primes[i];
 for(int j=p;j<=q;j++)
 {
 if(j>1)
 s[j*primes[i]-a]=true;//表示j*primes[i]是合数，这里采取了偏移
 }
 }
 }
 int main()
 {
 int a,b;
 solve1();
 while(~scanf("%d%d",&a,&b))
 {
 if(a==1) a++;
 memset(s,false,sizeof s);
 solve2(a,b);
 int min1=0,min2=0,max1=0,max2=0;
 int sum1=0x3f3f3f3f,sum2=-1;
 int t=-1;
 for(int i=0;i<=b-a;i++)  //求出距离最小的两个素数和距离最大的两个素数
 {
 if(!s[i])
 {
 if(t>=0)
 {
 if(sum1>i-t)//i-t表示两素数之间的距离
 {
 sum1=i-t;
 min1=t+a;
 min2=i+a;
 }
 if(sum2<i-t)
 {
 sum2=i-t;
 max1=t+a;
 max2=i+a;
 }
 }
 t=i;
 }
 }
 if(min1==0||min2==0||max1==0||max2==0)
 printf("There are no adjacent primes.\n");
 else
 printf("%d,%d are closest, %d,%d are most distant.\n",min1,min2,max1,max2);
 }
 return 0;
 }
*/
