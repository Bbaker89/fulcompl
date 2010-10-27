/*____________________________________________________________________________//
Project Name: Syntax Analyzer (Assignment 2)
Due: November 5, 2010

______________________________________________________________________________*/


#include <syntax.h>

void syntax::output_printer_flag()
{
	char rule;
	cout<<"\nWould you like to print the syntax production rules? (y/n)"
	cin>>rule;
	
	if (rule == 'n' || rule == 'N')
		PrintSwitch = true;
	else
		PrintSwitch = false;
}







bool syntax::Empty()
	{
		if(PrintSwitch == true)
			cout<<"<Empty> ::= Epsilon\n";
		
		return true;
	}