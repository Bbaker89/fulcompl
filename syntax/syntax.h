/*____________________________________________________________________________//
Project Name: Syntax Analyzer (Assignment 2)
Due: November 5, 2010

______________________________________________________________________________*/


// going to add the declarations for the class later  ----Chad--10/26/10

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class syntax
{
public:
	syntax();


	void printInfo();

	void output_printer_flag();
	//Lets the user choose to print the syntax messages or not

	void syntax_error(string a);
	//Used to send error messages and exit the program

	void lex();
	//used to get the next lexical items   --IN PROGRESS

	void SyntaxAnalysis();
	//The function to check an entire file for Rat10F compatiblity


	// Below are all of the syntax production rules
	bool Rat10F();
	bool Identifier();
	bool OptFunctionDefintions();
	bool FunctionDefinitions();
	bool Function();
	bool OptParameterList();
	bool ParameterList();
	bool Parameter();
	bool Qualifier();
	bool Body();
	bool OptDeclarationList();
	bool DeclarationList();
	bool Delcaration();
	bool IDs();
	bool StatementList();
	bool Statement();
	bool Compound();
	bool Assign();
	bool If();
	bool Return();
	bool Write();
	bool Read();
	bool While();
	bool Condition();
	bool Relop();
	bool Expression();
	bool ExpressionPrime();
	bool Term();
	bool TermPrime();
	bool Factor();
	bool Primary();
	bool Empty();


private:

ifstream readFile;
ofstream writeFile;
int line;
string lexeme;
string token;
bool PrintSwitch;
bool t;

};
