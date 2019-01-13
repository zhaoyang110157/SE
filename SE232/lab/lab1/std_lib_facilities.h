//
//  std_lib_facilities.h
//  calculator-lab1
//
//  Created by 朱朝阳 on 2018/10/1.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//

#ifndef std_lib_facilities_h
#define std_lib_facilities_h

 /* std_lib_facilities_h */
/*
 std_lib_facilities.h
 */

/*
 simple "Programming: Principles and Practice using C++ (second edition)" course header to
 be used for the first few weeks.
 It provides the most common standard headers (in the global namespace)
 and minimal exception/error support.
 Students: please don't try to understand the details of headers just yet.
 All will be explained. This header is primarily used so that you don't have
 to understand every concept all at once.
 By Chapter 10, you don't need this file and after Chapter 21, you'll understand it
 Revised April 25, 2010: simple_error() added
 
 Revised November 25 2013: remove support for pre-C++11 compilers, use C++11: <chrono>
 Revised November 28 2013: add a few container algorithms
 Revised June 8 2014: added #ifndef to workaround Microsoft C++11 weakness
 */




#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include <forward_list>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <array>
#include <regex>
#include<random>
#include<stdexcept>
 #include<stdlib.h>
//------------------------------------------------------------------------------

std::fstream out("/Users/zhuzhaoyang/Desktop/lab1_output.txt");
std::fstream in("/Users/zhuzhaoyang/Desktop/lab1_input.txt");

//------------------------------------------------------------------------------

typedef long Unicode;

//------------------------------------------------------------------------------

using namespace std;

inline void error(const string& s)
{
	throw runtime_error(s);
}

inline void error(const string& s, const string& s2)
{
	error(s+s2);
}

inline void error(const string& s, int i)
{
	ostringstream os;
	out<<s<<i;
	error(os.str());
}
#endif //H112
