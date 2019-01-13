//
//  CounterHeap.h
//  counterheap
//
//  Created by 朱朝阳 on 2018/12/8.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//

#ifndef CounterHeap_h
#define CounterHeap_h

#include "Heap.h"
#include <math.h>

/*
 * Class Heap
 * ----------
 * This is the class you should implement.
 * In this class you should use a maxHeap and a minHeap to store data
 * And your goal is to get a element with specific ranking in O(1) time complexity
 */

class CounterHeap
{
private:
	Heap<greater<int>> maxHeap;
	Heap<less<int>> minHeap;
	
	// A variable used to calculate breakPoint, your must init it in constructor
	double percentage;
	
	// BreakPoint means the target element's ranking from small to large
	// And TA have implemented the getBreakPoint() function for you, you should use this function to get the index
	int getBreakPoint();
	
public:
	/*
	 * Constructor: CounterHeap(double percent)
	 * Usage: CounterHeap counterHeap(0.2)
	 */
	CounterHeap(double percent);
	
	/*
	 * Constructor: CounterHeap(double percent, vector<int> init_elements)
	 * Usage: CounterHeap counterHeap(0.2, init_elements)
	 * ------------------------------------------------
	 * You should implement this Method with O(mlog(n)) time complexity (m = init_elements.size(), n = maxHeap.size()+minHeap.size())
	 */
	CounterHeap(double percent, vector<int> init_elements);
	
	/*
	 * Destructor: ~Heap()
	 * Usage: usually implicit
	 */
	~CounterHeap();
	
	/*
	 * Method: insert(int element)
	 * Usage: counterHeap.insert(1)
	 * ------------------------
	 * You should implement this Method with O(log(n)) time complexity (n = maxHeap.size()+minHeap.size())
	 */
	void insert(int element);
	
	/*
	 * Method: insert(vector<int> new_elements)
	 * Usage: counterHeap.insert(new_elements)
	 * ------------------------
	 * You should implement this Method with O(mlog(n)) time complexity (m = new_elements.size(), n = maxHeap.size()+minHeap.size())
	 */
	void insert(vector<int> new_elements);
	
	/*
	 * Method: erase(int element)
	 * Usage: counterHeap.erase(1)
	 * ------------------------
	 * You can try to implement this Method with O(log(n)) time complexity (n = elements.size())
	 */
	bool erase(int val);
	
	/*
	 * Method: target()
	 * Usage: counterHeap.target()
	 * ------------------------
	 * return the target element
	 * You should implement this Method with O(log(1)) time complexity
	 */
	int target();
	
	/*
	 * Method: size()
	 * Usage: counterHeap.size()
	 * ------------------------
	 * return the number of element in the CounterHeap
	 * You should implement this Method with O(log(1)) time complexity
	 */
	int size();
};

#endif /* CounterHeap_h */
