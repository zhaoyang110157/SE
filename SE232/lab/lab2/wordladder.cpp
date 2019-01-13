//
//  main.cpp
//  collecting interests-lab2
//
//  Created by 朱朝阳 on 2018/10/19.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//
/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name:Zhu Zhaoyang
 * Student ID:517021910798
 * This file is the starter project for the word ladder problem of Lab 2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <vector>
#include <map>
using namespace std;

//find the dest and init
void show_ans(vector<string> &ans);

//input and start function
void input_words(string &start, string &dest);

// read lexicon from file
void read_english(set<string> &english);

void show_ans(vector<string> &ans)
{
	cout << "Found ladder:";
	cout << ans[0];
	for (int i = 1; i < ans.size(); i++)
	{
		cout << "->" << ans[i];
	}
	cout << endl
	<< endl;
}

void input_words(string &start, string &dest)
{
	cout << "Enter start word (enter ':q' to quit):";
	cin >> start;
	if (start == ":q")
	{
		exit(0);
	}
	cout << "Enter destination word:";
	cin >> dest;
}

void read_english(set<string> &english)
{
	while (true)
	{
		cout << "Please enter filename containing source text:";
		string file_name;
		cin >> file_name;
		ifstream file_input(file_name.c_str());
		if (file_input.is_open())
		{
			string temp_word;
			while (getline(file_input, temp_word))
			{
				english.insert(temp_word);
			}
			break;
		}
	}
}

void findthedest( vector<string> &ans, set<string> &english, const string start, const string dest){
	queue<vector<string>> code;
	vector<string> tempvec;
	tempvec.push_back(start) ;
	code.push(tempvec);
	string now = start;
	while (now != dest){
		int cnt = 0;
		set<string> com;
		com.insert(now);
		while( cnt != now.size())
		{
			for(int i = 0; i < 26; i++)
			{
				string tempstr = now;
				tempstr[cnt] = 'a'+i;
				if(com.find(tempstr) == com.end())
				if( english.find(tempstr) != english.end())
				{
					tempvec.push_back(tempstr);
					code.push(tempvec);
					tempvec.pop_back();
					com.insert(tempstr);
				}
			}
			cnt++;
		}
		code.pop();
		tempvec=code.front();
		now = code.front() [code.front().size()-1 ];
	}
	ans.clear();
	for(size_t cnt = 0; cnt != code.front().size() ; cnt++)
		ans.push_back(code.front()[cnt]);
};

int main()
{
	// TODO: your code
	string start=" ",dest=" ";
	set<string> english;
	vector<string> ans;
	vector<string> *num=new vector<string>[20];
	read_english( english );

	
	while( true )
	{
		input_words( start , dest );
		findthedest(ans, english, start, dest);
		show_ans( ans );
	}
	delete[] num;
	return 0;
}
