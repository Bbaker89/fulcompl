/*____________________________________________________________________________//
 Project Name: Syntax Analyzer (Assignment 2)
 Due: November 5, 2010
 
 ______________________________________________________________________________*/









/* ############################ PROGRAMMER NOTES ##########################
 
 I am basing all of my code from the examples found on pages 91 - 92
 from the book.
 
 I have not tested any of these functions.
 
 
 
 
 To Do:
 
 Change the output file in the lexer to lexical.txt, so that the syntaxer
 knows where it is.
 
 ######################################################################## */




#include "syntax.h"

syntax::syntax(){
	string output;
	readFile.open("LexOutput.txt");
	cin >> t;
	cout<<"Where would you like to store the Output file?";
	cin>>output;
	writeFile.open(output.c_str());

	line = 0;
}

void syntax::printInfo(){
	if(PrintSwitch)
		writeFile<<"\nToken: "<<token<<"\tLexeme: "<<lexeme<<endl;
}

void syntax::output_printer_flag()
{
	char rule;
	cout<<"\nWould you like to print the syntax production rules? (y/n)";
	cin>>rule;

	if (rule == 'y' || rule == 'Y'){
		PrintSwitch = true;
		cout<<"\nPrinting is on.\n";
	}
	else{

		PrintSwitch = false;
		cout<<"\nPrinting is off\n";
	}
}


void syntax::syntax_error(string a){
	cout<<"\nError: "<<a<<endl;
	cout<<"The error was found on line #"<<line<<endl;
	cout<<"\nError with the syntax, now quitting....\n";

	writeFile<<"\nError: "<<a<<endl;
	writeFile<<"The error was found on line #"<<line<<endl;
	writeFile<<"\nError with the syntax, now quitting....\n";
//	exit(1);
}

void syntax::lex(){

	readFile >> lexeme >> token;
	if( t == true){//test
	cout << "TEST" << lexeme << " " << token << endl;}
	if(token == "NewLine"){
		line++;
		lex();
	}
}

void syntax::SyntaxAnalysis(){
	output_printer_flag();
	lex();	
	if(Rat10F())
		cout<<"\n\nThe syntax of the file is correct.";
}


////////////////////////////   Syntaxical Analsis Below //////////////////////////////////////

bool syntax::Rat10F(){
	bool valid = true;
	if(PrintSwitch == true)
			printInfo(); writeFile << "<Rat10F> ::= $$<Opt Function Definitions> $$ <Opt Declaration List> <Statement List> $$\n";
	if(lexeme == "$$")	{

		OptFunctionDefintions();
		

		if(lexeme == "$$")		{
			OptFunctionDefintions();
			StatementList();
		}
		else{
			syntax_error("Expected $$");
}

		if(lexeme != "$$")
			syntax_error("Expected $$");


	}
	else
		syntax_error("Expected $$");

	return valid;
}

bool syntax::Identifier(){
	if(token == "Identifier")
		return true;
	else
		return false;
}



bool syntax::OptFunctionDefintions()
{
	if( t == true){/*Test*/ writeFile << " Entered Opt Func Definition" << endl; 	printInfo();}
	lex();
	bool valid = true;
	if( t == true){//test2
	cout << "TEST2" << lexeme << " " << token << endl;}
	if(FunctionDefinitions()){
		if(PrintSwitch)
			printInfo(); writeFile<<"<Opt Function Definitions> ::= <Function Definitions>\n";
	}
	else{

		printInfo(); writeFile<<"<Opt Function Definitions> ::= <Empty>";
		Empty();
	}

	return valid;
}


bool syntax::FunctionDefinitions(){
	if( t == true){/*Test*/ writeFile << "Entered Func Definition" << endl; 	printInfo();}

	bool valid = true;
	if( t == true){//test3
	cout << "TEST F Def" << lexeme << " " << token << endl;}
	if(Function()){

		if(FunctionDefinitions()){
			if(PrintSwitch)
				printInfo(); writeFile<<"<Function Definitions> ::= <Function><Function Definitions>\n";
		}else{
			if(PrintSwitch)
				printInfo(); writeFile<<"<Function Definitions> ::= <Function>\n";
		}
	}
	return valid;
}

bool syntax::Function(){
	if( t == true){/*Test*/ writeFile << "Entered Func" << endl; 	printInfo();}
	bool valid = false;
	if( t == true){//test4
	cout << "TEST4" << lexeme << " " << token << endl;}
	if(PrintSwitch)
		printInfo(); writeFile<<"<Function> ::= function<Identifier>[<Opt Parameter List> ] <Opt Decleration List> <>\n";
	if(lexeme == "function"){
	if( t == true){/*Test*/ writeFile << "Entered If in Function" << endl;}
		lex();
		if(token == "Identifier"){
			lex();
	if( t == true){/*Test*/ writeFile << "Entered If in function for Lexeme" << endl;}
			if(lexeme == "["){
				if(OptParameterList()){
					if(lexeme == "]"){
						if(OptDeclarationList()){
							if(Body()){
								valid = true;
							}
							else
								syntax_error("Expecting Body");
						}
						else
							syntax_error("Expecting Opt Declaration List");
						}
					}
					else 
						syntax_error("Expecting Opt Parameter List");
				}
				else
					syntax_error("Expecting [");
			}
			else
					syntax_error("Expecting Identifier");
	}
	return valid;
}

bool syntax::OptParameterList(){
	if( t == true){/*Test*/ writeFile << "Entered Opt Parameter list" << endl; 	printInfo();}
	bool valid = false;
	if( t == true){//test5
	cout << "TEST5" << lexeme << " " << token << endl;}
	lex();
	if(ParameterList()){

		if(PrintSwitch)
			printInfo(); writeFile<<"<Opt Parameter List> ::= <Parameter List>\n";
		valid = true;
	}
	else{
		if(PrintSwitch)
			printInfo(); writeFile<<"<Opt Parameter List> ::= <Empty>\n";
		Empty();
		valid = true;
	}

	return valid;
}

bool syntax::ParameterList(){
	if( t == true){/*Test*/ writeFile << "Entered Parameter List" << endl;	printInfo();}
	bool valid = false;
	if(Parameter()){
		lex();
		if(lexeme == ","){
			printInfo(); writeFile<<"<Parameter List> ::= <Parameter>,<Parameter List>\n";
			if(ParameterList())
				valid = true;
			else 
				valid = false;
		}
		else {
			printInfo(); writeFile<<"<Parameter List> ::= <Parameter>\n";
			valid = true;
		}
	}
	return valid;
}

bool syntax::Parameter()
{
	if( t == true){/*Test*/ writeFile << "Entered PArameter" << endl;}
	bool valid = false;
	printInfo(); writeFile<<"<Parameter> ::= <IDS> : <Qualifier>\n";
	if(IDs())
	{
		lex();

		if(lexeme == ":")
		{
			lex();
			if(Qualifier())
				valid = true;
		}
		else
			syntax_error("Expecting :");
	}
	return valid;
}

bool syntax::Qualifier()
{
	if( t == true){/*Test*/ writeFile << "Entered Qualifier" << endl;}

	bool valid = true;

	if(lexeme == "int")
	{
		printInfo(); writeFile<<"<Qualifier> ::= int\n";
	}
	else if(lexeme == "real")
	{
		printInfo(); writeFile<<"<Qualifier> ::= real\n";
	}	
	else if(lexeme == "boolean")
	{
		printInfo(); writeFile<<"<Qualifier> ::= boolean\n";
	}
	else
	{
		valid = false;
	}
	return valid;
}

bool syntax::Body()
{
	if( t == true){	/*Test*/ writeFile << "Entered Body" << endl; printInfo();}
	lex();
	bool valid = false;
	if(PrintSwitch)
		printInfo(); writeFile<<"<Body> ::= {<Statement List>}\n";
	if(lexeme == "{")
	{
		if(StatementList())
		{
			lex();

			if(lexeme =="}")
			{
				valid = true;
			}
			else 
				syntax_error("Expecting }");
		}
	}
	else
		syntax_error("Expecting {");

		return valid;
}

bool syntax::OptDeclarationList()
{
	if( t == true){/*Test*/ writeFile << "Entered OPT DEc List" << endl;printInfo();}
	if(DeclarationList())
	{
		printInfo(); writeFile<<"<Opt Declaration List> ::= <Declaration List>\n";
	}
	else	
	{
		printInfo(); writeFile<<"<Opt Declaration List> ::= Empty\n";
	}

	return true;
}

bool syntax::DeclarationList()
{
	if( t == true){/*Test*/ writeFile << "Entered Dec list" << endl; printInfo();}
	bool valid = true;

	//CHECK FOR RECURSION

	return valid;
}

bool syntax::Delcaration()
{
	if( t == true){/*Test*/ writeFile << "Entered Decleration" << endl; printInfo();}
	bool valid = false;
	if(PrintSwitch)
		printInfo(); writeFile<<"<Delclaration> ::= <Qualifier><IDs>\n";
	if(Qualifier())
	{
		if(IDs())
		{
			valid=true;
		}
	}

	return valid;
}

bool syntax::IDs()
{
	if( t == true){/*Test*/ writeFile << "Entered IDS" << endl; printInfo();}
	bool valid = false;
	if(Identifier()){
		if(lexeme == ","){
			printInfo(); writeFile<<"<IDS> ::= <Identifier>,<IDS>\n";
			if(IDs())
				valid = true;
			else 
				valid = false;
		}
		else {
			printInfo(); writeFile<<"<IDS> ::= <Identifier>\n";
			valid = true;
		}
	}
	return valid;
}

//working on this below
bool syntax::StatementList()
{
	if( t == true){/*Test*/ writeFile << "Entered Statement List" << endl;	printInfo();}
	bool valid = false;
	if(Statement()){
		lex();
		if(Statement()){
			printInfo(); writeFile<<"<Statement List> ::= <Statement><Statement List>\n";
			if(StatementList())
				valid = true;
			else 
				valid = false;
		}
		else {
			printInfo(); writeFile<<"<Statement List> ::= <Statement>\n";
			valid = true;
		}
	}
	return valid;
}

bool syntax::Statement()
{
	if( t == true){/*Test*/ writeFile << "Entered Statement" << endl; printInfo();}
	bool valid = false;
	lex();
	if(lexeme == "{"){
		if(PrintSwitch)
			writeFile<<"<Statement> ::= <Compound>\n";
		Compound();
	}
	else if(token == "Identifier"){
		valid = true;
		if(PrintSwitch)
			writeFile<<"<Statement> ::= <Assign>\n";
		Assign();
	}	

	else if (lexeme == "if"){
			valid = true;
			if(PrintSwitch)
				writeFile<<"<Statement> ::= <If>\n";
			If();
	}


	else if (lexeme == "return"){
			valid = true;
			if(PrintSwitch)
				writeFile<<"<Statement> ::= <Return>\n";
			Return();
	}

	else if (lexeme == "write"){
			valid = true;
			if(PrintSwitch)
				writeFile<<"<Statement> ::= <Write>\n";
			Write();
	}

	else if (lexeme == "read"){
			valid = true;

		if(PrintSwitch)
				writeFile<<"<Statement> ::= <Read>\n";
			Read();
	}

	else if (lexeme == "while"){
			valid = true;

		if(PrintSwitch)
			writeFile<<"<Statement> ::= <While>\n";
		While();
	}
	else{
		syntax_error("Expecting Statement");
		valid = false;
	}
	return valid;
}

bool syntax::Compound()
{
	if( t == true){/*Test*/ writeFile << "Entered Compund" << endl;}
	bool valid = false;

	if(lexeme == "{"){
		lex();
		if(StatementList()){
			lex();
			if(lexeme =="}"){
				valid = true;

				if(PrintSwitch)
					printInfo(); writeFile<<"<Compound> ::= { <Statment List> }\n";
			}
			else
				syntax_error("Expecting }");
		}
	}
	return valid;
}

bool syntax::Assign()
{
	if( t == true){/*Test*/ writeFile << "Entered Assign" << endl; printInfo();}
	bool valid = false;
	lex();
	if(Identifier()){
		lex();
		if(lexeme ==":="){
			lex();
			if(Expression()){
				valid = true;

				if(PrintSwitch)
					printInfo(); writeFile<<"<Assign> ::= <Identifier> := <Expression>\n";
			}
		}
		else
			syntax_error("Expecting :=");
	}

	return valid;
}

bool syntax::If()
{
	if( t == true){/*Test*/ writeFile << "Entered IF" << endl; printInfo();}
	bool valid = true;
//work on
	return valid;
}

bool syntax::Return()
{
	if( t == true){/*Test*/ writeFile << "Entered Return" << endl; printInfo();}
	bool valid = false;
	lex();
	if(lexeme == ";"){
		printInfo(); writeFile<<"<Return> :: = return;\n";		
		valid = true;
	}
	else if (Expression()){
		printInfo(); writeFile<<"<Return> :: = return<Expression>;\n";		
	}
	else
		syntax_error("Expecting ;");
	return valid;
}

bool syntax::Write()
{
	if( t == true){/*Test*/ writeFile << "Entered Write" << endl;}
	bool valid = false;
	if(PrintSwitch)
		printInfo(); writeFile<<"<Write> :: = write (<Expression>);\n";
	if(lexeme == "write"){
		lex();

		if(lexeme =="("){
			lex();
			if(Expression()){
				lex();
				if(lexeme == ")"){
					lex();
					if(lexeme == ";"){
						valid = true;
					}
				}
			}
		}
		else
			syntax_error("Expecting (");
	}
	else
		syntax_error("Expecting write");

	return valid;
}

bool syntax::Read()
{
	if( t == true){/*Test*/ writeFile << "Entered Read" << endl;}
	bool valid = false;
	lex();
	if(PrintSwitch)
		printInfo(); writeFile<<"<Read> ::= read (<IDs>);\n";
	if(lexeme =="read"){
		lex();
		if(lexeme == "(")
		{
			lex();
			if(IDs()){
				lex();
				if(lexeme == ")"){
					lex();
					if(lexeme ==";")
					{
						valid = true;
					}
					else
						syntax_error("Expecting ;");
				}
				else
					syntax_error("Expecting )");
			}
			else
				syntax_error("Expecting IDs");
		}
		else
			syntax_error("Expecting (");
	}
	else
		syntax_error("Expecting read");

	return valid;
}

bool syntax::While()
{
	if( t == true){/*Test*/ writeFile << "Entered While" << endl;}
	bool valid = false;

	lex();

	if(lexeme == "while"){
		lex();
		if(lexeme == "("){
			lex();
			if(Expression()){
				lex();
				if(lexeme == ")"){
					lex();
					if(Expression()){
						if(PrintSwitch)
							printInfo(); writeFile<<"<While> ::= while (<Condition>)<Statement>\n";

						valid =  true;
					}
					else
						syntax_error("Expecting Expression");
				}
				else
					syntax_error("Expecting )");
			}
			else
				syntax_error("Expecting Expression");
		}
		else
			syntax_error("Expecting (");
	}
	else
		syntax_error("Expecting while");

	return valid;
}

bool syntax::Condition()
{
	if( t == true){/*Test*/ writeFile << "Entered Condition" << endl;}
	bool valid = false;

	if(Expression()){
		lex();
		if(Relop()){
			lex();
			if(Expression())
			{
				valid = true;
			}
			else{
				syntax_error("Expecting Expression");
			}
		}
		else{
			syntax_error("Expecting Relop");
		}
	}
	else{
		syntax_error("Expecting Expression");
	}

	return valid;
}

bool syntax::Relop()
{
	if( t == true){/*Test*/ writeFile << "Entered Relop" << endl; printInfo();}
	bool valid = true;

	if(lexeme == "="){
		if(PrintSwitch){
			printInfo(); 
			writeFile<<"<Relop> ::= =\n";
		}
	}	
	else if (lexeme == "/=") {
		if(PrintSwitch){ 
			printInfo(); 
			writeFile<<"<Relop> ::= /=\n";
		}
	}
	else if (lexeme == ">") {
		if(PrintSwitch){
			printInfo(); writeFile<<"<Relop> ::= >\n";
		}
	}
	else if (lexeme == "<"){
			if(PrintSwitch){
				printInfo();
				writeFile<<"<Relop> ::= <\n";
			}
	}
	else if(lexeme == "=>"){
			if(PrintSwitch){
				printInfo(); 
				writeFile<<"<Relop> ::= =>\n";
			}
	}
	else if(lexeme == "<="){
			if(PrintSwitch){
				printInfo(); 
				writeFile<<"<Relop> ::= <=\n";
			}
	}
	else {
		syntax_error("Expecting Relop Operator");
		valid = false;
	}


	return valid;
}

bool syntax::Expression()
{
	if( t == true){/*Test*/ writeFile << "Entered Expression" << endl; printInfo();}
	bool valid = false;

	if(Term())
	{
		lex();
		if(ExpressionPrime())
		{
			valid = true;	
		}
	}
	else
		syntax_error("Expecting Term");

	return valid;
}

bool syntax::ExpressionPrime()
{
	if( t == true){/*Test*/ writeFile << "Entered E Prime" << endl; printInfo();}
	bool valid = false;

	if(lexeme == "+"|| lexeme == "-")
	{
		lex();
		if(Term())
		{
			if(ExpressionPrime())
			{
				valid = true;
			}

		}
		else
			syntax_error("Expecting Expression");
	}
	else if (Term()){
		valid = true;
	}
	else
		syntax_error("Expecting + or -");

		return valid;
}

bool syntax::Term()
{
	if( t == true){/*Test*/ writeFile << "Entered Term" << endl; printInfo();}
	bool valid = false;

	if(Factor())
	{
		if(TermPrime())
		{
			valid = true;	
		}
	}
	else
		syntax_error("Expecting Term");
		return valid;
}

bool syntax::TermPrime()
{
	if( t == true){/*Test*/ writeFile << "Entered Term Prime" << endl; printInfo();}
	bool valid = false;

	if(lexeme == "*"|| lexeme == "/")
	{
		lex();
		if(Factor())
		{
			if(TermPrime())
			{
				valid = true;
			}

		}
		else
			syntax_error("Expecting Factor");
	}
	else if (Factor()){
		valid = true;
	}
	else
		syntax_error("Expecting * or /");
	return valid;
}

bool syntax::Factor()
{
	if( t == true){/*Test*/ writeFile << "Entered Factor" << endl; printInfo();}
		bool valid = false;

		if(lexeme == "-")
		{
			lex();

			if(Primary())
			{
				if(PrintSwitch)
					printInfo(); writeFile<<"<Expression> ::= - <Primary>\n";

				valid = true;
			}
		}
		else if(Primary())
		{
			if(PrintSwitch)
				printInfo(); writeFile<<"<Expression> ::= <Primary>\n";

			valid = true;
		}
		return valid;
	}

bool syntax::Primary()
{
	if( t == true){/*Test*/ writeFile << "Entered Primary" << endl; printInfo();}
		bool valid = false;
		if(token == "Real"){
			valid = true;

			if(PrintSwitch)
				printInfo(); writeFile<<"<Primary> :== Real\n";
		}
		else if(token == "Identifier"){
			valid = true;
			if(PrintSwitch)
				printInfo(); writeFile<<"<Primary> ::= Identifier\n";
		}
		else if(lexeme == "("){
			if(Expression());{
				lex();

				if(lexeme == ")"){
					valid = true;
					if(PrintSwitch)
						printInfo(); writeFile<<"<Primary ::= (Expression)\n";
				}
				else
					syntax_error("Expecting )");
			}
		}
		else if(token == "Integer"){
			valid = true;
			if(PrintSwitch)
				printInfo(); writeFile<<"<Primary> ::= Integer\n";
		}
		else if(lexeme == "true"){
			valid = true;
			if(PrintSwitch)
				printInfo(); writeFile<<"<Primary> ::= TRUE\n";
		}
		else if(lexeme == "false"){
			valid = true;
			if(PrintSwitch)
				printInfo(); writeFile<<"<Primary> ::= FALSE\n";
		}
		else 
			syntax_error("Expecting Primary");

		return valid;
	}

bool syntax::Empty()
{
	if( t == true){/*Test*/ writeFile << "Entered Empty" << endl;}
	if(PrintSwitch)
		writeFile<<"<Empty> ::= Epsilon\n";

	return true;
}
