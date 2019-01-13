//
//  main.cpp
//  Output string in reverse, plus space
//
//  Created by 朱朝阳 on 2018/9/15.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//
#include<iostream>
#include <vector>
using namespace std;
int main(){
	vector<int> vec;
	vector<char> array;
	int val=0;
	int num;
	char ch;
	bool store=false,first=false;
	while(ch = cin.get()){
		if(ch!=' '&&ch!='\n')
		{
			first=true;//终于遇到了第一个单词
			val++;
			store=true;
			array.push_back(ch);
		}//符合要求的时候
		
		   else  //如果是空格，将空格前的数插入到vec中，开始记录新的数
			   if(first&&store)
			   {
				   store=false;//只要放一次
				   vec.push_back(val);
			   }
		if(ch == '\n')//如果是换行符，结束
		{
			break;
		}
	}
	/*for(int i=0;i<array.size();i++)
		cout<<array[i];
	cout<<endl;
	cout<<array.size()<<endl<<vec.size()<<endl;
	for(int i=0;i<vec.size();i++)
		cout<<vec[i]<<endl;
	检测用代码*/
		num=vec.size();
	for(int i=num-1;i>0;i--)
	{
		if(vec[i]>vec[i-1])
		{
			for(int j=vec[i-1];j<vec[i];j++)cout<<array[j];
			cout<<" ";
		}
	}
	if(first)
	for(int i=0;i<vec[0];i++)
		cout<<array[i];
	else	    cout<<"invalid";
		return 0;
}

/*
#include <iostream>
#include <vector>
using namespace std;

typedef struct Words{
	int len;
	char * start;
}Words;
void reverseSentence(char * c)
{
	vector<Words> S; //存储单词的栈
	
	Words w;
	w.start = c;
	w.len = 0;
	for (int i = 0; c[i] != '\0'; i++)
	{
		if (c[i] != ' ')
		{
			w.len++;
		}
		else
		{
			if (w.len != 0)
			{
				S.push_back(w);
				w.start = c + i + 1;
				w.len = 0;
			}
			else //跳过多余的空格
			{
				w.start = c + i + 1;
			}
		}
	}
	if (w.len != 0) //压入最后一个词
	{
		S.push_back(w);
	}
	
	while (!S.empty())
	{
		Words w = S.back();
		for (int i = 0; i < w.len; i++)
		{
			cout << *(w.start + i);
		}
		cout << ' ';
		S.pop_back();
	}
	cout << endl;
}

int main()
{
	char * c = "  I   am  a student.";
	reverseSentence(c);
	
	return 0;
}
标答
 */
/*
 #include<iostream>
 #include<string.h>
 #include<stdio.h>
 #include <vector>
 using namespace std;
 void Split(const string& src,const string& separator, vector<string>& dest)
{
	string str = src;
	string substring;
	string::size_type start = 0, index;
	dest.clear();
	index = str.find_first_of(separator,start);
	do
	{
		if (index != string::npos)
		{
			substring = str.substr(start,index-start );
			dest.push_back(substring);
			start =index+separator.size();
			index = str.find(separator,start);
			if (start == string::npos) break;
		}
	}while(index != string::npos);
	
	//the last part
	substring = str.substr(start);
	dest.push_back(substring);
}
int main(){
	string str;
	getline(cin,str);
	vector<string> arr;
	Split(str," ",arr);
	int index=arr.size();
	for(int i=index-1;i>0;i--)
		cout<<arr.at(i)<<" ";
	cout<<arr[0];
	
	
	return 0;
}*/
/*
int main(){
	string str;
	vector<string> arr;
	int index = 0;
	while(cin>>str){//string遇到空格会停止
		arr.push_back(str);
		index++;
		char ch = getchar();//通过getchar()来判断最后输入回车符结束
		if(ch == '\n') break;
	}

	for(int i=index-1;i>0;i--)
		cout<<arr.at(i)<<" ";
	cout<<arr[0];

	
	return 0;
}*/

/*
 方案一，缺点设有上限
 #include<iostream>
#include<cstring>
#include<vector>
using namespace std;
int main()
{
	char sentence[10000];
	int i=0;
	while((sentence[i]=getchar())!='\n')
		i++;
	getchar();
	char *tokenPtr=strtok(sentence," ");
	vector<char*> array;
	int num=0;
	while(tokenPtr!=NULL)
	{
		num++;
		array.push_back(tokenPtr);
		tokenPtr=strtok(NULL," ");
	}
	for(int i=num-1;i>=0;i--)
		cout<<array[i]<<endl;
	//cout << "After strtok,sentence=" <<tokenPtr<<endl;
	return 0;
}
*/
