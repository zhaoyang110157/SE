//
//  main.cpp
//  game of life
//
//  Created by 朱朝阳 on 2018/11/10.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
int main(){
	vector<int> temp;
	temp.push_back(0);
	temp.push_back(1);
	temp.push_back(0);
	vector<vector<int>> board;
	board.push_back(temp);
	temp.clear();
	temp.push_back(0);
	temp.push_back(0);
	temp.push_back(1);
	board.push_back(temp);
	temp.clear();
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(1);
	board.push_back(temp);
	temp.clear();
	temp.push_back(0);
	temp.push_back(0);
	temp.push_back(0);
	board.push_back(temp);
	int length,width,all;
	length = 4;
	width = 3;
	all = length * width;
	int now[12];

	for (int cnt = 0; cnt < all; cnt++)
	{
		int live = 0;
		for(int i = 0;i < 9;i++)
		{
			if(i == 4) continue;
			int x = cnt/width+i/3-1;
			int y = cnt%width+i%3-1;
			if(x>=0 && y>=0 && x<length && y<width && board[x][y]==1) live++;
		}
		if(board[cnt/width][cnt%width]==1)
		{
			if(live == 2 || live == 3 ) now[cnt]=1;
			else now[cnt]=0;
		}
		else{
			if(live == 3) now[cnt]=1;
			else now[cnt]=0;
		}
		int t=now[cnt];
		t++;
	
	}
	for(int cnt = 0; cnt<all ; cnt++)
	{
		board[cnt/width][cnt%width] = now[cnt];
		cout<<now[cnt];
	}
}

