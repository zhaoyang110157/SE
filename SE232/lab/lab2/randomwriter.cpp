//
//  main.cpp
//  lab2-2
//
//  Created by 朱朝阳 on 2018/10/27.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//
/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name:Zhu Zhaoyang
 * Student ID:517021910798
 * This file is the starter project for the random writer problem of Lab 2.
 * [TODO: extend the documentation]
 */
///Users/zhuzhaoyang/Downloads/RandomWriter/aLetter.txt
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
using namespace std;
#define MAX_CHAR_NUM 100

// get filename
void read_file(ifstream &file_input);

// get order number
int read_order();

// build model
void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model);

// write
void random_write(const int &order, map<string, vector<char>> &model);

void read_file(ifstream &file_input)
{
	while (true)
	{
		cout << "Please enter filename containing source text:";
		string file_name;
		cin >> file_name;
		file_input.open(file_name.c_str());
		if (file_input.is_open())
		{
			cout<<"Open Successfully";
			break;
		}
	}
}

int read_order()
{
	cout<<"Please give me the order(an integry from 1 to 10):";
	int temp;
	cin>>temp;
	return temp;
	// TODO: your code here
}

void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model, map<string,int> &count)
{
	char in;
	string temp = " ";
	file_input>>noskipws;
	for(int cnt = 0; cnt < order; cnt++)
	{
		file_input >> in;
		temp [cnt] = in;
	}
	while(file_input >> in){
		if(model.find(temp) !=  model.end())
		{
			model[temp].push_back( in );
			count[temp]=1;
		}
		else {
			vector< char > tempvec;
			tempvec.push_back(in);
			model.insert(make_pair(temp, tempvec));
			count[temp]++;
		}
		temp.erase(temp.begin());
		temp.push_back(in);
	}
	// TODO: your code here
}

void random_write(const int &order,  map<string, vector<char>> &model,  map<string,int> &count)
{
	string mostshow;
	mostshow = count.begin()->first;
	for(auto cnt = count.begin() ; cnt != count.end() ; cnt++)
		if(cnt->second > count[mostshow] ) mostshow = cnt->first;
	cout<<mostshow;
	string seed = mostshow;
	for( int cnt = 0 ; cnt < 2000-order ; cnt++)
	{
		int tempint = rand()%(model[seed].size());
		char tempchar = model[seed][tempint];
		cout<<tempchar;
		seed.erase( seed.begin() );
		seed.push_back( tempchar );
	}
	
}

int main()
{
	srand((unsigned)time(NULL));
	ifstream file_input;
	read_file ( file_input );
	
	int order;	order=read_order();
	map< string , vector<char> > model;
	map< string , int> count;

	model_read( file_input , order, model , count);
	
	random_write(order, model,count);
	// TODO: your code here
	return 0;
}
