//
//  main.cpp
//  Redundant Parentheses
//
//  Created by 朱朝阳 on 2018/10/27.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//

#include <string>
#include <iostream>
using namespace std;


string simplify(string &input);
size_t findleft(const string &input , size_t rhs);
bool isOperator(char get);
bool allmulordiv( const string &input);
string simplify(string &input){
	size_t lhs = 0;//left hand side
	size_t rhs = 0;//right hand side
	char front,back;//the one before the parenthess and the one back
	bool can;//if we can simplify this pair of parenthesses
	
	while( (rhs = input.find( ')' , rhs)) != string :: npos)//find a ')' from the begining. And as if the expression is valid, this kind of way can find all the pairs.
	{
		lhs = findleft( input, rhs );
		if( lhs > 0 && isOperator( input [ lhs - 1 ] ))	front = input [ lhs - 1 ];
		else front = '+';  //'+' is omnipotent. When it comes to else, it means lhs is the first char of the string or that it uses a ab-type to discurb a*b. These two situation will not disturb the result,so why not give it a '+'?
	       if( rhs < input.size()-1 && isOperator( input [ rhs + 1 ] ))
			back = input [ rhs + 1 ];
		else back = '+'; //the same like before
		
		if( rhs - lhs == 2) can = true; //the simplest situation
		else  if ( front == '/') can = false;// first situation
		//if the front is '/', the content should be a divsor. The only situation that can be simplified has been solved in the simplest. ---a/(b)
		else  if ( front == '*' || front == '-' ) //situation two
			can = allmulordiv( input.substr( lhs , rhs - lhs) );
		else 	can = back == '+' || back == '-' || allmulordiv( input.substr( lhs , rhs - lhs) );// this situation is that the front is'+'
		
		if(can) {
			input.erase(rhs,1).erase(lhs,1);//right first, so we needn't minus 1
			rhs--; //ok, we still need to minus 1 , for the length has been minus 1;
		}
		else rhs++; // this pair can't be simplified, so we step in and got next.
		
	}
	return input;
}

size_t findleft(const string & input, size_t rhs){
	int countOfRight = 1;
	for(--rhs; rhs >= 0; --rhs){
		if(input[rhs] == ')')  ++ countOfRight;
		else if(input[rhs] == '('){
			--countOfRight;
			if(!countOfRight) break;
		}
	}// to solve ((( ))) situation or (()())situation
	return rhs;
}

bool isOperator(char c){
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool allmulordiv(const string& input)
{
	size_t len = input.size();
	for(int i = 0; i < len; ++i){
		if(input[i] == '('){
			int cnt = 1;// to solve ((( ))) situation or (()())situation
			for(++i; true; ++i){
				if(input[i] == '(') ++cnt;
				else if(input[i] == ')'){
					--cnt;
					if(!cnt) break;
				}
			}
			++i;
		}
		if(input[i] == '+' || input[i] == '-') return false;// no all mul or div
	}
	return true;
}

int main(){
	ios::sync_with_stdio(false);
	string input;
	while(cin>>input){
		cout<<simplify(input)<<endl;
	}
	return 0;
}
