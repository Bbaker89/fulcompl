/*____________________________________________________________________________//
Project Name: Syntax Analyzer (Assignment 2)
Name: Baker, Blake & Herman, Chad
Class: CPSC 323 Section: 02
Professor: Song-James Choi Ph.D
Due: November 5, 2010

______________________________________________________________________________*/


#include <syntax.h>

void syntax::output_printer_flag()
{
	char rule;
	cout<<"\nWould you like to print the syntax production rules? (y/n)"
	cin>>rule;
	
	if (rule == 'n' || rule == 'N')
		globalPrintSwitch = true;
	else
		globalPrintSwitch = false;
}