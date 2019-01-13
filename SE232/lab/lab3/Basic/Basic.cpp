/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: 517021910798]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"

using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   TokenScanner scanner;
   bool exist=true;

   while (exist) {
      try { 
	string line = getLine();
	int type;
	int linenumber=-1;
	string statementstring;   
	Statement *statement;
    	scanner.ignoreWhitespace();
   	scanner.scanNumbers();
   	scanner.setInput(line);	
	
	statementstring = scanner.nextToken();
	if(statementstring[0] >= '0' && statementstring[0] <='9')
	{
		linenumber = stringToInteger(statementstring);
		statementstring = scanner.nextToken();
		
		if(statementstring != "")
		{
			stringstream strm(line);
			string key; string tmp; strm>>tmp; strm>>key; strm>>tmp;
			if(program.delword.find(statementstring) != program.delword.end())
				type = program.delword.find(statementstring)->second;
			
			switch(type)
			{
			case 0:	
			  {
				statement =new delstatement(type,NULL);
				break;//REM
			  }
			case 2://PRINT
			case 3://INPUT
			  {
				statement = new delstatement(type,parseExp(scanner));
				break;
			  }
			case 1://LET
			  {
				string token = scanner.nextToken();
				Expression *tmp=new IdentifierExp(token);
				if(scanner.nextToken() == "=" && !(token=="REM" ||token=="LET" ||token=="QUIT" ||token=="PRINT" ||token=="INPUT"||token=="LIST" ||token=="HELP" ||token=="RUN" ||token=="CLEAR" ||token=="GOTO" ||token=="THEN" ||token=="IF" ||token=="END"))
					{  
						
						statement = new delstatement(type,tmp,parseExp(scanner)); 
					}
				else	error("SYNTAX ERROR");
				break;
			  }
			case 4://GOTO
				statement = new delstatement(type,readE(scanner));
				break;
			case 5://IF
			  {
				Expression *lhs = readE(scanner,1);
//cout<<lhs->toString()<<endl;
				string op = scanner.nextToken();
//cout<<op[0]<<endl;
				Expression *rhs = readE(scanner);
//cout<<rhs->toString()<<endl;
				string op1 = scanner.nextToken();
				if(op1!="THEN") error("SYNTAX ERROR");
				Expression *r = readE(scanner);
//cout<<r->toString()<<endl;
				statement = new ifstatement(type,lhs,rhs,op,r);
				break;
			  }
			default:
			  {
				Expression *exp = NULL;
				statement = new delstatement(type,exp);
				break;
			  }
			}
			program.addSourceLine(linenumber, line);
			program.setParsedStatement(linenumber, statement);
		}
		else
			{
			 program.removeSourceLine(linenumber);
			}
	}
	else{
		if(program.imiword.find(statementstring) != program.imiword.end())
			type = program.imiword.find(statementstring)->second;
		else error("SYNTAX ERROR");
		
		switch(type)
			{
			case 0: //QUIT
				exist = false ;
				break;
			case 2://PRINT
			  {
				Expression *exp = parseExp(scanner);
				int value = exp->eval(state);
   				cout << value << endl;
				break;
			  }
			case 3://INPUT
			  {	
				statement = new imistatement(type,parseExp(scanner));
				statement->execute(state);
				break;
			  }
			case 1://LET
			  {	
				string token = scanner.nextToken();
				if(token=="REM" ||token=="LET" ||token=="QUIT" ||
					token=="PRINT" ||token=="INPUT"||
					token=="LIST" ||token=="HELP" ||token=="RUN" ||	
					token=="CLEAR" ||token=="GOTO" ||token=="THEN" ||
					token=="IF" ||token=="END")
					error("SYNTAX ERROR");
				Expression *tmp=new IdentifierExp(token);
				if(scanner.nextToken() == "=")
					{ 
						statement = new imistatement(type,tmp,parseExp(scanner)); 
						statement->execute(state);
					}
				else	error("SYNTAX ERROR");
				break;
			  }
			case 4://LIST
			   {
				for(map<int,string>::iterator tmp=program.numtoline.begin(); tmp!=program.numtoline.end(); ++tmp)
					cout<<tmp->second<<endl;	
				break;
			   }
			case 5://HELP
			  {
				cout<<"Yet another basic interpreter"<<endl;
				break;
			  }
			  
			case 6://RUN
			   {
//cout<<"start"<<endl;
				int cnt = program.getFirstLineNumber();
				int next;
//cout<<cnt<<endl;
				while( cnt )
				{
					
					next = program.getNextLineNumber(cnt);
//cout<<cnt<<endl;
					program.numtostat[cnt]->setnextlinenum(next);
//cout<<"?"<<endl;
					program.numtostat[cnt]->execute(state);
//cout<<":"<<endl;
					cnt = program.numtostat[cnt]->getnextlinenum();
//cout<<"!"<<endl;
					if(cnt<0) break;
					if(program.numtostat.find(cnt) == program.numtostat.end()) 
						error("LINE NUMBER ERROR");
				}
				break;
			   }
			default:
			  {
				program.clear();
				state.clear();
				break;
			  }
			}//switch
	}//else
	//processLine(getLine(),program,state);

      }//try
  
	
     catch (ErrorException & ex) {
         cout << ex.getMessage() << endl;
      }
   }//while
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */
/*
void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   Expression *exp = parseExp(scanner);
   int value = exp->eval(state);
   cout << value << endl;
   delete exp;
}*/
