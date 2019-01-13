//
//  CounterHeap.cpp
//  counterheap
//
//  Created by 朱朝阳 on 2018/12/8.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//

#include "CounterHeap.h"


CounterHeap::CounterHeap(double percent)
{
	percentage = percent;
	// you code here
}

CounterHeap::CounterHeap(double percent, vector<int> init_elements)
{
	percentage = percent;
	insert( init_elements );
	// you code here
}

CounterHeap::~CounterHeap()
{
	// you code here
}

int CounterHeap::getBreakPoint()
{
	return ceil((minHeap.size() + maxHeap.size()) * percentage);
}

void CounterHeap::insert(int element)
{
	
	if( maxHeap.size() == 0 )
	{
		maxHeap.insert( element );
	}
	else{
		int maxtop = maxHeap.top();
		if( maxtop < 0 ) return;
		if( maxtop <= element ) minHeap.insert( element );
		else	maxHeap.insert( element );
		
		if(maxHeap.size() > getBreakPoint())
		{
			int tmp = maxHeap.pop();
			maxHeap.shift_down(make_pair(0, 0));
			minHeap.insert( tmp );
			return;
		}
		if(maxHeap.size() < getBreakPoint() )
		{
			int tmp = minHeap.pop();
			maxHeap.insert( tmp );
			maxHeap.shift_down(make_pair(0, 0));
			return;
		}
	}
	
	// you code here
}

void CounterHeap::insert(vector<int> new_elements)
{
	for(int cnt = 0 ; cnt < new_elements.size() ; ++cnt)
		insert( new_elements[ cnt ] );
	// you code here
}

bool CounterHeap::erase(int val)
{
	if( val > target() )	minHeap.erase( val );
	else	maxHeap.erase( val );
	if(maxHeap.size() > getBreakPoint())
	{
		int tmp = maxHeap.pop();
		minHeap.insert( tmp );
		return true;
	}
	if(maxHeap.size() < getBreakPoint() )
	{
		int tmp = minHeap.pop();
		maxHeap.insert( tmp );
		return true;
	}
	return true;
	// you code here
}

int CounterHeap::target()
{
	return maxHeap.top();
	// you code here
}

int CounterHeap::size()
{
	return ( minHeap.size() + maxHeap.size() );
	// you code here
}
