/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"

#include "../StanfordCPPLib/simpio.h"
using namespace std;

bool all(string tmp)
{
for(int i=1 ; i<tmp.length()-1 ; ++i)
	if(tmp[i]<'0' || tmp[i]>'9') return false;
return true;
}

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

delstatement::delstatement(){
	type = -1;
}
delstatement::delstatement(int ty,Expression *l,Expression *r){
	type = ty;
	lhs = l;
	rhs = r;
}

delstatement::~delstatement(){
	delete lhs;
	delete rhs;
}
void delstatement::execute(EvalState &state){
	switch(type)
	{
		case 2://PRINT
		  {
			string tmp = lhs->toString();
			int value ; 
			if(tmp[0] >= '0' && tmp[0] <='9') 	
			{	
				value = lhs->eval(state);
			}
			else
			{
				if(state.isDefined(tmp))
				{value = state.getValue(tmp);}
				else error("VARIABLE NOT DEFINED");
			}
			cout<<value<<endl;
			break;
		  }
		case 3://INPUT
		  {
			cout<<" ? ";
			string tmp;
			tmp=getLine();
			while(tmp[0] != '-' && (tmp[0] <'0' ||tmp[0]>'9') || !all(tmp)) 
				{
					cout<<"INVALID NUMBER"<<endl;
					cout<<" ? ";tmp=getLine();
				}
			 state.setValue(lhs->toString(),stoi(tmp));
			break;
		  }	
		case 1://LET
		  {
			string var=lhs->toString();
			int value = rhs->eval(state);
			state.setValue(var,value);
			break;
		  }
		case 4://GOTO
			linenumber=lhs->eval(state);
			break;
		
		case 6: linenumber = -1;
		default:	break;
	}
}
void delstatement::setnextlinenum(int linenum)
{
	linenumber=linenum;
}
int delstatement::getnextlinenum()
{
	return linenumber;
}






ifstatement::ifstatement(){
	type = -1;
}
ifstatement::ifstatement(int ty,Expression *l,Expression *r,string ch1,Expression *n){
	type = ty;
	ch=ch1[0];
//cout<<ch1<<" "<<ch<<endl;
	next=n;
	lhs = l;
	rhs = r;
}

ifstatement::~ifstatement(){
	delete lhs;
	delete rhs;
	delete next;
}
void ifstatement::execute(EvalState &state){
	switch(type)
	{
		case 5://IF
		  {
			int left = lhs->eval(state);
			int right = rhs->eval(state);
			int n = next->eval(state);
//cout<<left<<" "<<right<<" "<<n<<" "<<ch<<endl;
			bool flag=false;
			switch(ch)
			{
			case '>': 	if(left>right) flag=true;
					break;
			case '<':	if(left<right) flag = true;
					break;
			default :	if(left==right) flag=true;
					break;
			}
//cout<<flag<<endl;
			if(flag)  linenumber=n;
//cout<<linenumber<<endl;
			break;
		  }
		default:	break;
	}
}
void ifstatement::setnextlinenum(int linenum)
{
	linenumber=linenum;
}
int ifstatement::getnextlinenum()
{
	return linenumber;
}










imistatement::imistatement(){
	type = -1;
 
}
imistatement::imistatement(int ty,Expression *l,Expression *r){
	type = ty;
	lhs = l;
	rhs = r;
}

imistatement::~imistatement(){
	delete lhs;
	delete rhs;
}
void imistatement::execute(EvalState &state){
	switch(type)
	{
		case 2://PRINT
		  {
			string tmp = lhs->toString();
			int value ; 
			if(tmp[0] >= '0' && tmp[0] <='9') 	
			{	
				value = lhs->eval(state);
			}
			else
			{
				if(state.isDefined(tmp))
				{value = state.getValue(tmp);}
				else error("VARIABLE NOT DEFINED");
			}
			cout<<value<<endl;
			break;
		  }
		case 3://INPUT
		  {
			cout<<" ? ";
			string tmp;
			tmp=getLine();
			while(tmp[0] != '-' && (tmp[0] <'0' ||tmp[0]>'9') || !all(tmp)) 
				{
					cout<<"INVALID NUMBER"<<endl;
					cout<<" ? ";tmp=getLine();
				}
			 state.setValue(lhs->toString(),stoi(tmp));
			break;
		  }	
		case 1://LET
		  {
			string var=lhs->toString();
			int value = rhs->eval(state);
			state.setValue(var,value);
			break;
		  }

		default:
		  {
			break;
		  }
	}
	
}
void imistatement::setnextlinenum(int linenum)
{
	linenumber=linenum;
}
int imistatement::getnextlinenum()
{
	return linenumber;
}

