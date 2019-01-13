//
//  Heap.h
//  counterheap
//
//  Created by 朱朝阳 on 2018/12/8.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//

#ifndef Heap_h
#define Heap_h
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

/*
 * Class Heap
 * ----------
 * This is the class you should implement.
 * It is a template class, Compare can be greater<int>, less<int> and so on.
 * When you define a Heap like Heap<greater<int>>, it should be a maxHeap (who's top this the max element)
 * When you define a Heap like Heap<less<int>>, it should be a minHeap (who's top this the min element)
 * So, when you want to compare two element while implement the member function, you shoud use the member variable cmp, rather than <,<=,>,>=
 */
template<class Compare>
class Heap
{
private:
	// use elements to store the element
	map<int,vector<int>> elements;
	map<int,vector<pair<int,int>>> loc;
	// cmp is a comparer that can help you to compare two element's priority
	// Usage:
	// cmp(element_1, element_2)
	// if element_1's priority is higher than element_2, it will return true, otherwise, return false
	// Example:
	// when you define a Heap like Heap<greater<int>>, it means Compare is greater<int>, and cmp is a instance of greater<int>
	// So, cmp(1,2) and cmp(1,1) will return false and cmp(2,1) will return true
	// when you define a Heap like Heap<less<int>>, it means Compare is less<int>, and cmp is a instance of less<int>
	// So, cmp(2,1) and cmp(1,1) will return false and cmp(1,2) will return true
	// By this way, you can implement minHeap and maxHeap using one class
	Compare cmp;
	
	pair<int,int> dumIndex;
	// the Top element's index, can make the code more readable
	// It's up to you whether to use it
	pair<int,int> topIndex;
	
	// Some help function, can improve the code structure
	// It's up to you whether to use them
	pair<int,int> getParentIndex(pair<int,int> index);
	pair<int,int> getLeftIndex(pair<int,int> index);
	pair<int,int> getRightIndex(pair<int,int> index);
	bool isInRange(pair<int,int> index);
	void swap(pair<int,int> index_1, pair<int,int> index_2);
	pair<int,int> findIndex(int element);
	int getValue(pair<int,int> index);
	void print(map<int,vector<pair<int,int>>> &lo);
public:
	
	void shift_up(pair<int,int> index);
	void shift_down(pair<int,int> index);
	
	
	
	/*
	 * Constructor: Heap()
	 * Usage: Heap<greater<int>> maxHeap
	 */
	Heap();
	
	/*
	 * Constructor: Heap(vector<int> init_elements)
	 * Usage: Heap<greater<int>> maxHeap(init_elements)
	 * ------------------------------------------------
	 * You should implement this Method with O(mlog(n)) time complexity (m = init_elements.size(), n = elements.size())
	 */
	Heap(vector<int> init_elements);
	
	/*
	 * Destructor: ~Heap()
	 * Usage: usually implicit
	 */
	~Heap();
	
	/*
	 * Method: insert(int element)
	 * Usage: maxHeap.insert(1)
	 * ------------------------
	 * Add the new element in to the end of elements and shift_up this element
	 * You should implement this Method with O(log(n)) time complexity (n = elements.size())
	 */
	void insert(int element);
	
	/*
	 * Method: insert(vector<int> new_elements)
	 * Usage: maxHeap.insert(new_elements)
	 * ------------------------
	 * Add the new element in to the end of elements and shift_up this element one by one
	 * You should implement this Method with O(mlog(n)) time complexity (m = new_elements.size(), n = elements.size())
	 */
	void insert(vector<int> new_elements);
	
	/*
	 * Method: erase(int element)
	 * Usage: maxHeap.erase(1)
	 * ------------------------
	 * Swap this element with the elements's last element, delete the last element, and shift_down the swapped element
	 * You should implement this Method with O(log(n)) time complexity (n = elements.size())
	 */
	bool erase(int element);
	
	/*
	 * Method: pop()
	 * Usage: maxHeap.pop()
	 * ------------------------
	 * Swap the top element with the elements's last element, delete and return the last element, and shift_down the swapped element
	 * You should implement this Method with O(log(n)) time complexity (n = elements.size())
	 */
	int pop();
	
	/*
	 * Method: top()
	 * Usage: maxHeap.top()
	 * ------------------------
	 * return the top element
	 * You should implement this Method with O(log(1)) time complexity
	 */
	int top();
	
	/*
	 * Method: size()
	 * Usage: maxHeap.size()
	 * ------------------------
	 * return the number of element in the Heap
	 * You should implement this Method with O(log(1)) time complexity
	 */
	int size();
};

template<class Compare>
Heap<Compare>::Heap()
{
	topIndex = make_pair(0,0);
	dumIndex = make_pair (0,-1);
	elements.clear();
	loc.clear();
}

template<class Compare>
Heap<Compare>::~Heap()
{
	elements.clear();
}

template<class Compare>
Heap<Compare>::Heap(vector<int> init_elements)
{
	topIndex = make_pair(0,0);
	dumIndex = make_pair (0, -1);
	insert( init_elements );
}

template<class Compare>
void Heap<Compare>::insert(int element)
{
	//cout<<"insert "<<element<<endl;
	
	int result = exp2( dumIndex.first );
	if( result == dumIndex.second + 1 ) {
		dumIndex.first += 1; dumIndex.second = 0;
		vector<int> tmp;
		elements.insert ( make_pair ( dumIndex.first , tmp) );
	}
	else dumIndex.second += 1;
	elements[dumIndex.first].push_back( element );
	
	
	if(loc.find(element)!=loc.end())
		loc[element].push_back(dumIndex);
	else
	{
		vector<pair<int,int>> tmploc;
		tmploc.push_back(dumIndex);
		loc.insert(make_pair( element , tmploc ) );
	}
	shift_up(dumIndex);
	
}

template<class Compare>
void Heap<Compare>::insert(vector<int> new_elements)
{
	for(int cnt = 0 ; cnt < new_elements.size() ; ++cnt)
		insert ( new_elements[cnt] );
	//print(loc);
}

template<class Compare>
bool Heap<Compare>::erase(int element)
{
	
	pair<int,int> tmpIndex = findIndex( element );
	if(tmpIndex.second < 0 || tmpIndex.first >= elements.size() ) return false;
	swap(tmpIndex,dumIndex);
	
	if(loc[element].size() == 1) loc.erase( element );
	else loc[element].erase( loc[element].begin() ); //IF the target has only one, erase the target in the location map
	
	if(elements[dumIndex.first].size() == 1)
		elements.erase( dumIndex.first );
	else	elements[dumIndex.first].pop_back();
	//erasr the last element in the map elements
	
	if(dumIndex.second == 0 && dumIndex.first!=0)
	{
		dumIndex.first -=1;
		dumIndex.second = exp2(dumIndex.first) - 1;
	}
	else dumIndex.second -= 1;
	//change the dumIndex
	
	shift_down( tmpIndex );
	//adjust the order
	return true;
}

template<class Compare>
int Heap<Compare>::pop()
{
	int tmp = top() ;
	erase(tmp);
	return tmp;
}

template<class Compare>
int Heap<Compare>::top()
{
	if(dumIndex.second == -1) return -1;
	if( !elements.empty() )
		return elements[0][0];
	else return 0;
}

template<class Compare>
int Heap<Compare>::size()
{
	int size(0);
	for(int cnt = 0 ;cnt < dumIndex.first ; ++cnt )
		size += exp2( cnt );
	size += dumIndex.second + 1;
	return size;
}

template<class Compare>
inline pair<int,int> Heap<Compare>::getParentIndex(pair<int,int> index)
{
	return make_pair(index.first-1,index.second/2);
}

template<class Compare>
inline pair<int,int> Heap<Compare>::getLeftIndex(pair<int,int> index)
{
	return make_pair(index.first+1,index.second*2);
}

template<class Compare>
inline pair<int,int> Heap<Compare>::getRightIndex(pair<int,int> index)
{
	return make_pair(index.first+1,index.second*2+1);
}

template<class Compare>
bool Heap<Compare>::isInRange(pair<int,int> index)
{
	int size(0);
	for(int cnt = 0 ;cnt < index.first ; ++cnt )
		size += exp2( cnt );
	size += index.second + 1;
	return (size <= this->size());
}

template<class Compare>
void Heap<Compare>::swap(pair<int,int> index_1, pair<int,int> index_2)
{
	//print(loc);
	int first = getValue ( index_1 );
	int second = getValue ( index_2 );
	//cout<<"swap "<<first<<" and "<<second<<endl;
	elements[index_1.first][index_1.second] = second;
	elements[index_2.first][index_2.second] = first;
	int firstloc = find( loc[first].begin(),loc[first].end(),index_1 ) - loc[first].begin();
	int secondloc = find(loc[second].begin(),loc[second].end(), index_2) - loc[second].begin();
	//	cout<<"value	location	index"<<endl;
	//	cout<<first<<" "<<firstloc<<" "<<index_1.first<<" "<<index_1.second<<endl;
	//	cout<<second<<" "<<secondloc<<" "<<index_2.first<<" "<<index_2.second<<endl;
	loc[second][secondloc] = index_1;
	loc[first][firstloc] = index_2;
}

template<class Compare>
inline pair<int,int> Heap<Compare>::findIndex(int element)
{
	if(loc.find(element)!= loc.end())
		return loc[element][0];
	else return make_pair(0,-1);
}

template<class Compare>
inline int Heap<Compare>::getValue( pair<int,int> index)
{
	if( isInRange( index ) )
		return elements[index.first][index.second];
	else return 0;
}

template<class Compare>
void Heap<Compare>::shift_up(pair<int,int> tmp)
{
	pair<int,int> tmpp = getParentIndex( tmp );
	for(int cnt = tmp.first ; cnt > 0; --cnt)
	{
		if(cmp( getValue(tmp) , getValue(tmpp)))
		{
			swap(tmp,tmpp);
			tmp=tmpp;
			if( tmpp == topIndex ) break;
			tmpp = getParentIndex( tmp );
		}
		else break;
	}
}

template<class Compare>
void Heap<Compare>::shift_down(pair<int,int> tmp)
{
	pair<int,int> tmpl;
	pair<int,int> tmpr;
	pair<int,int> tmpp;
	for(int cnt = tmp.first ; cnt < dumIndex.first - 1; ++cnt)
	{
		tmpl = getLeftIndex( tmp );
		tmpr = getRightIndex( tmp );
		int left = getValue( tmpl );
		int right = getValue( tmpr );
		tmpp = cmp(left,right) ? tmpl : tmpr;
		if(!cmp( getValue(tmp) , getValue(tmpp)))
		{
			swap(tmp,tmpp);
			tmp=tmpp;
			if( tmpp == topIndex ) break;
		}
		else break;
	}
}
template<class Compare>
void Heap<Compare>::print(map<int,vector<pair<int,int>>> &a)
{
	cout<<"print:"<<endl;
	for(map<int,vector<pair<int,int>>>::iterator cnt=a.begin();cnt!=a.end();++cnt)
	{
		cout<<cnt->first<<" : " ;
		for (int j=0;j<cnt->second.size();++j)
		{
			cout<<cnt->second[j].first<<" "<<cnt->second[j].second<<";    ";
		}
		cout<<endl;
	}
}


#endif /* Heap_h */
