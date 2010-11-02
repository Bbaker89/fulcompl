/*____________________________________________________________________________//
 Project Name: Lexical Analyzer (Assignment 1)
 
 Due: October 1, 2010
 
 ______________________________________________________________________________*/


//______________________________Includes______________________________________
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include "syntax.cpp"

using namespace std;


//______________________________Functions listed_______________________________
/*
 getLexeme =>
 Function takes an input stream and reads in the next lexeme available. It then 
 runs the lexeme through a serious of ifs and checks if it needs to be ran 
 through a coresponding FSM. Depending on the resulting FSM state or the lexeme's
 value it determines its token type and prints both to an output file.
 */
void getLexeme(ifstream & fin, ofstream &fout, int &lineCounter);
void getInput(string &a);
void getOutput(string &b);


/*_____________________________Bool Functions___________________________________
 isKeyword => if given string is in the keyword list given returns 'true' else 
 'false'
 
 isOperator => if given string is operator returns 'true' else returns 'false'
 -if string is begining of two character operator it checks next 
 character to see if it is a special two character (<= >= := ) if is then adds to
 the string else puts back the character in the file both returns true.
 
 isSeprator => if given string is separator returns 'true' else returns 'false'
 -if string is begining of two character separator it checks next 
 character to see if it is a special two character ($$) if is then adds to the 
 string and returns true else puts back the character in the file and returns 
 false.
 
 isOpOrSp => Checks the given character to see if it is the start of a new token.
 -Such as an Operator or a separator
 
 */
bool isKeyword(string s);
bool isOperator(string & s, ifstream & fin);
bool isseparator(string & s, ifstream & fin);
bool isOpOrSp(char c);





//________________________________Main_________________________________________
int main() {
	ifstream fin;
	string inFile, outFile;
	int line;
	getInput(inFile);
	getOutput(outFile);
	fin.open(inFile.c_str());
	if(fin.fail())
	{
		cout<<"Input file path inccorect, please renter the path and try again.\n\n";
	}
	else
	{
		ofstream fout;
		fout.open(outFile.c_str());
		while(!(fin.eof())){//while file not empty keep going
			getLexeme(fin, fout, line);
		}//end while
	}
	syntax syn;
	syn.SyntaxAnalysis();
	return 0;
}//end main


//______________________________Functions_______________________________________


//----------------------------getLexeme-----------------------------------------

void getInput(string &a)
{
	cout<<"Please enter the input file:";
	cin>>a;
}


void getOutput(string &b)
{
	cout<<"Please enter an output file:";
	cin>>b;
	b = "LexOutput.txt";

	}


void getLexeme(ifstream & fin, ofstream &fout, int &lineCounter){
	int state = 0, x = 0, y = 0;// x is current state y is the input
	int digitFSM[3][3] = {{0,1,2},{1,2,2},{2,2,2}}; 
	int idFSM[4][4] = {{1,3,3,3},{1,1,2,3},{1,1,2,3},{3,3,3,3}};
	char c,n;// c is current char n is next
	string s = "";// s is the Lexeme
	fin.get(c);
	s += c;// add character to the current lexeme


	if(c == '\n')
	{
		fout<<lineCounter<<"			NewLine"<<endl;
		lineCounter++;
	}

	if(ispunct(c)){
		if(isOperator(s, fin))
			fout << s << "			Operator" <<  endl;
		else if(isseparator(s,fin))
			fout << s << "			Separator" << endl;
		else
			fout << s << "			Unknown" << endl;
	}//end 	if(ispunct(c))
	else if (isalpha(c)){
		fin.get(n);
		state = 1;//set state to 1 to simulate first letter in FSM
		while(!(isOpOrSp(n) || isspace(n) || fin.eof())){
			if(isalpha(n))
				y = 0;
			else if(isdigit(n))
				y = 1;
			else if(n == '_')
				y = 2;
			else
				y = 3;
			state = idFSM[x][y];
			x = state; //set current state
			s += n;//add character to lexeme
			fin.get(n);
		}//endwhile(!(isOpOrSp(n) || isspace(n) || fin.eof()))
		fin.putback(n);
		switch (state) {
				//only accepting state in idFSM is 1
			case 0: 
				fout << s << "			Unknown" <<  endl;
				break;
			case 1: 
				if(isKeyword(s))
					fout << s << "			Keyword" <<  endl;
				else
					fout << s << "			Identifier" <<  endl;
				break;
			case 2:
			case 3: 
				fout << s << "			Unknown" <<  endl;
				break;
			default:
				fout << "This should never print" << endl;
		}//end switch Statement
	}//endif (isalpha(c))
	else if(isdigit(c)){
		fin.get(n);
		while(!(isOpOrSp(n) || isspace(n) || fin.eof())){
			if(isdigit(n))
				y = 0;
			else if(n == '.')
				y = 1;
			else
				y = 2;
			state = digitFSM[x][y];
			x = state;
			s += n;
			fin.get(n);
		}// endwhile (!(isOpOrSp(n) || isspace(n) || fin.eof()))
		fin.putback(n);
		switch (state) {//use state to determine accepting or non
				//only accepting states in FSM is 0 and 1
			case 0: 
				fout << s << "			Integer" <<  endl;
				break;
			case 1: 
				fout << s << "			Real" <<  endl;
				break;
			case 2: 
				fout << s << "			Unknown" <<  endl;
				break;
			default: fout << "This should never print" << endl;
		}//end switch Statement
	}//end elseif isdigit(c)
}//end getLexeme

//----------------------------isKeyword-----------------------------------------
bool isKeyword(string s){
	if(s == "int"|| s == "if"|| s == "else"|| s == "endif"|| s == "while"|| 
	   s == "return"||s == "read"|| s == "char"|| s == "write"||
	   s == "float"||s == "double"||s == "break"||s == "boolean"|| 
	   s == "long"||s == "function"|| s == "case"|| s == "switch" || s == "real" ||
	   s == "true" || s == "false")
		return true;
	else
		return false;
}

//----------------------------isOperator-----------------------------------------
bool isOperator(string & s, ifstream & fin){
	//Operator list : = - * / = <= >= :=  
	char b;
	if (s == "=" || s == ">" || s == "<" || s == "+" || s == "-" || s == "*"
		|| s == "/" || s == "=" || s == ":" ) { 
		if ( s == ">") {// check for >=
			fin.get(b);
			if ( b == '=')
				s += b;
			else
				fin.putback(b);
		}// end if ( s == '=')
		else if( s == ":"){//check for :=
			fin.get(b);
			if ( b == '=')
				s += b;
			else
				fin.putback(b);
		}//end else if( c == ':')
		else if( s == "<"){// check for <=
			fin.get(b);
			if ( b == '=')
				s += b;
			else
				fin.putback(b);
		}
		else if( s == "="){// check for =>
			fin.get(b);
			if ( b == '>')
				s += b;
			else
				fin.putback(b);
		}//end 

		else if( s == "/"){// check for /=
			fin.get(b);
			if ( b == '=')
				s += b;
			else
				fin.putback(b);
		}//end 
		return true;
	}//end if (...)
	else 
		return false;
}//end isOperator

//----------------------------isseparator---------------------------------------
bool isseparator(string & s, ifstream & fin){
	//separator list ( ) { } [ ] $$ ;   
	char b;
	if (s == "(" || s == ")" || s == "{" || s == "}" || s == "[" || s == "]"
		|| s == "$" || s == ";" || s == ","){
		if( s == "$" && !fin.eof()){//check for $$
			fin.get(b);
			if( b == '$')
			{ s += b; return true;}
			else
			{fin.putback(b); return false;}
		}// end if ( c == '$')
		else
			return true;
	}//end if (..)
	else
		return false;
}//end isseparator

//----------------------------isOpOrSp------------------------------------------
bool isOpOrSp(char c){
	if (c == '=' || c == '>' || c == '<' || c == '+' || c == '-' || c == '*'
		|| c == '/' || c == '=' || c == ':' ||c == '(' || c == ')' 
		|| c == '{' || c == '}' || c == '[' || c == ']'|| c == '$' 
		|| c == ';' || c == ',')
		return true;
	else 
		return false;
}//end isOpOrSp
