//
//  main.cpp
//  calculator-lab1
//
//  Created by 朱朝阳 on 2018/10/1.
//  Copyright © 2018年 朱朝阳. All rights reserved.
//




/*
 	This program implements a basic expression calculator.
 	Input from cin; output to cout.
 	The grammar for input is:
 	Statement:
 	Expression
 	Print
 	Quit
 	Print:
 		;
 	Quit:
 		q
 	Expression:
 	Term
 	Expression + Term
 	Expression – Term
 	Term:
 	Primary
 	Term * Primary
 	Term / Primary
 	Term % Primary
 	Primary !
 	Primary:
 	Number
 	( Expression )
 	– Primary
 	+ Primary
 	sqrt (Primary)
 	Number:
 	floating-point-literal
 Input comes from cin through the Token_stream called ts.
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
std::fstream in("/Users/zhuzhaoyang/Downloads/input.txt");

//------------------------------------------------------------------------------


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

using namespace std;



inline int keep_window_open(const char& a){char ch;while(in>>ch)if(ch==a) return 0;return 0;};
inline void keep_window_open(){};

const char number='8';
const char print=';';
const string prompt=">";
const string result="=";

double ANS=0;

class Token {
public:
	char kind;
	double value;
	Token(char ch)    // make a Token from a char
	:kind(ch), value(0) { }
	Token(char ch, double val)     // make a Token from a char and a double
	:kind(ch), value(val) { }
};

//------------------------------------------------------------------------------11*12/(1+1/2))+5*(6-4)*31;


class Token_stream
{
public:
	Token_stream();
	Token get();
	void putback(Token t);
	void ignore(char c);
private:
	bool full;
	Token buffer;
};

Token_stream::Token_stream()
:full(false), buffer(0){}

void Token_stream::putback(Token t)
{
	if (full) error("Error");//error("putback() into a full buffer");
	buffer = t;             // copy t to buffer
	full = true;            // buffer is now full
}

Token Token_stream::get()
{
	if (full)
	{
		full=false;
		return buffer;
	}
	
	char ch;
	in>>ch;
	switch(ch)
	{
		case ';':
		case 'q':
		case '%':
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '!':
			return Token(ch);			//let each character represent themselves
		case'.':			//a float-point-literal can start with a dot
		case'0': case'1': case'2': case'3': case'4':
		case'5': case'6': case'7': case'8': case'9':		//normal number
		{
			in.putback(ch);		//put digit back into the input stream
			double val;
			in>>val;		//read a floating-point number
			return Token(number, val);
		}
		case'A':
		{
			in>>ch;
			if(ch=='N'){
				in>>ch;
				if(ch=='S') return Token(number,ANS);
			}
			error("Error");//error("Bad Token");
		}
		default:
			error("Error");//error("Bad Token");
	}
	return 0;
	// *****This place is strange for that on Xcode I am not able to bulit without this sentence.
}

void Token_stream::ignore(char c)
 //using c to represent the type of Token
{
	//first look in buffer
	if(full&&c==buffer.kind){
		full=false;
		return;
	}
	full =false;
	
	//now search input;
	char ch=0;
	while(in>>ch)
		if(ch==c)return;
	
}
Token_stream ts;

//=============

class Variable{
public:
	string name;
	double value;
	Variable(string n,double v):name(n),value(v){}
};
vector<Variable> var_table;

double get_value(string s){
	// return value of the Variable named s
	for(int i=0;i<var_table.size();i++)
		if(var_table[i].name==s) return var_table[i].value;
	error("Error");//error("get undenied variable:",s);
	return 0;
}

void set_value(string s, double d) // Sets variable's value
{
	for (int i = 0; i<=var_table.size(); ++i)
		if (var_table[i].name == s) {
			var_table[i].value = d;
			return;
		}
	error("Error");//error("set: undefined name ",s);
}
//============= 1++++2;1!;2!;3!;4!;

double expression();

double term();

double primary() {
	double lval=0  ;
	Token t = ts.get();
	switch(t.kind) {
		case '!':error("Error");// error("! need left value");
		case '(':
		{
			double d = expression();lval=d;
			t = ts.get();
			if (t.kind != ')')
			{
				ts.putback(t);
				error("Error");//error("')'expected");
			}
			t=ts.get();
			while(t.kind=='!'){
				if (lval < 0 || lval != int ( lval ) ) error("Error");//error("!");
				for (int i = 1; i < lval; i++) { // Get a multiplication of all numbers before x (including x)
					d*=i;
				}
				if (d == 0) lval = 1;
				else lval = d;
				d=lval;
				t=ts.get();
			}
			ts.putback(t);
				return lval;
				break;
		}
		case number:{
			double x;x =lval=t.value;
			t=ts.get();
			while(t.kind=='!'){
				if(lval<0||lval!=int(lval)) error("Error");//error("!");
				for (int i = 1; i < lval; i++) { // Get a multiplication of all numbers before x (including x)
					x*=i;
				}
				if (x== 0) lval = 1;
				else lval=x;
				t=ts.get();
			}
			ts.putback(t);
			return lval;
			break;

		}
			
		case'+': {
			double d = primary();
			lval=d;
			t=ts.get();
			while(t.kind=='!'){
				if(lval<0||lval!=int(lval))  error("Error");//error("!");
				for (int i = 1; i < lval; i++) { // Get a multiplication of all numbers before x (including x)
					d*=i;
				}
				if (d == 0) lval = 1;
				else lval = d;
				d=lval;
				t=ts.get();
			}
			ts.putback(t);
			return lval;
			break;
		}
		case '-':{
			double d = primary();
			lval=d;
			t=ts.get();
			while(t.kind=='!'){
				if(lval<0||lval!=int(lval)) error("Error");//error("!");
				for (int i = 1; i < lval; i++) { // Get a multiplication of all numbers before x (including x)
					d*=i;
				}
				if (d == 0) lval = 1;
				else lval = d;
				d=lval;
				t=ts.get();
			}
			ts.putback(t);
			return -lval;
			break;
		}
		case ')': error("Error");//error("'(' needed");
			return 0;
		default:
			error("Error");//error("primary expected");
			return 0;
	}
}

double term() {
	double lval = primary();
	Token t = ts.get();
	while(true) {
		switch(t.kind) {
			case '*':
				lval *= primary();
				t = ts.get();
				break;
			case '/':
			{
				double d = primary();
				if (d == 0) error("Error");//error("divide by zero");
				lval /= d;
				t = ts.get();
				break;
			}
			case '%':
			{
				double d=primary();
				int i1=int(lval);
				if(i1!=lval) error("Error");//error("left-hand operand");
				int i2=int(d);
				if(i2!=d) error("Error");//error("right-hand operand");
				if(i2==0) error("Error");//error("right-hand zero");
				lval=i1%i2;
				t=ts.get();
				break;
			}
			default:
				ts.putback(t);
				return lval;
		}
	}
}

double expression() {
	double lval = term();
	Token t = ts.get();
	while(true) {
		switch(t.kind) {
			case '+':
				lval+=term();
				t = ts.get();
				break;
			case '-':
				lval-=term();
				t = ts.get();
				break;
			default:
				ts.putback(t);
				return lval;
				break;
		}
	}
}

void clean_up_mess(){

	ts.ignore(print);

}
void calculate(){
	while(in){
	try{
		Token t = ts.get();
		while(t.kind==print) t=ts.get();
		if (t.kind == 'q'){
			keep_window_open();
			return;
		}
		ts.putback(t);
		ANS=expression();
		t=ts.get();
		if(t.kind==print)
		out << result << ANS << '\n';
		else {
			error("Error");//error("'('needed");
		}
	}
	catch(exception& e){
		out<<e.what()<<endl;
		clean_up_mess();
	}
	}
	
}

int main()
try {
	in.clear();
	calculate();
	keep_window_open();
	return 0;
}

		
catch(runtime_error& e) {
	out<<e.what()<< '\n';
	keep_window_open('~');
	return 1;
}
catch(...) {//all other exceptions
	out<< "exception \n";
	keep_window_open('~');
	return 2;
}
