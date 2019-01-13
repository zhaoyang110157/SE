/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;
Program::Program() {
	numtostat.clear();
	delword.clear();
	imiword.clear();
	imiword["QUIT"]=0;
	imiword["LET"]=1;
	imiword["PRINT"]=2;
	imiword["INPUT"]=3;
	imiword["LIST"]=4;
	imiword["HELP"]=5;
	imiword["RUN"]=6;
	imiword["CLEAR"]=7;

	delword["REM"]=0;//	delword[]=;
	delword["LET"]=1;
	delword["PRINT"]=2;
	delword["INPUT"]=3;
	delword["GOTO"]=4;
	delword["IF"]=5;
	delword["END"]=6;
   // Replace this stub with your own code
}

Program::~Program() {
	numtostat.clear();
	delword.clear();
	imiword.clear();
   // Replace this stub with your own code
}

void Program::clear() {
	numtoline.clear();
	numtostat.clear();
   // Replace this stub with your own code
}

void Program::addSourceLine(int lineNumber, string line) {
	numtoline[lineNumber]=line;
   // Replace this stub with your own code
}

void Program::removeSourceLine(int lineNumber) {
	numtoline.erase(lineNumber);
   // Replace this stub with your own code
}

string Program::getSourceLine(int lineNumber) {
	map<int,string>::iterator tmp=numtoline.find(lineNumber);
	if(tmp == numtoline.end())	return "";
	else return tmp->second;
    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
	numtostat[lineNumber]=stmt;
   // Replace this stub with your own code
}

Statement* Program::getParsedStatement(int lineNumber) {
	map<int,Statement*>::iterator tmp=numtostat.find(lineNumber);
	if(tmp == numtostat.end()) 
	{
		delstatement* tmp1=new delstatement(-1,NULL);
		return tmp1;
	}
	else return tmp->second;
  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
	
   	if(numtostat.empty())	return -1;
	else 
	{
		map<int,string>::iterator tmp=numtoline.begin();
		return tmp->first;
	}
    // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
	map<int,string>::iterator tmp=numtoline.find(lineNumber);
	tmp++;
	if(tmp!=numtoline.end())
	{
		return tmp->first;
	}
	
   	return -1;    
 // Replace this stub with your own code
}
