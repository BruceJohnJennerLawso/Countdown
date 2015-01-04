#include "TCmdMenu.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#define NEWLINE '\n'
#define TAB '\t'
#define VTAB '\v'
#define BEEP '\a'
#define BACK '\b'
using namespace std;

#define Stylechar2 "--"

int TCMD_Input_int(string prompt);
string TCMD_Input_string_with_tab(string prompt);
bool TCMD_Compare_string(string i, string comp);
void ExitCall();

vector<TCmdMenu*> Linkslist;

TCmdMenu::TCmdMenu(void)
{	cout << "Bad constructor call of TCmdMenu";
	delete this;
}

// Main menu type constructor /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

TCmdMenu::TCmdMenu(string menu_id, string menu_name)
{	menuid = menu_id;
	menuname = menu_name;
	Linkslist.push_back(this);		
}

// Intermediate Menu Constructor //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

TCmdMenu::TCmdMenu(string above_menu, string menu_id, string menu_name)
{	menuid = menu_id;
	menuname = menu_name;
	Linkslist.push_back(this);
	Stringlist.push_back(above_menu);					
}


void TCmdMenu::menu()
{	int nswitch = 1;			// Default set for the Menu heading display.
	string i;					// The input string to send to.

	while (true)				// The core Menu loop.
	{	if (nswitch == 1)		
		{	cout << Stylechar2 << menuname << Stylechar2 << NEWLINE << endl;	
		}	// That conditional output of the menu heading. Only called at the times where it looks right, so the switch is automatically set to 0 (off) at the top of the loop, and may be changed later on
		nswitch = 0;			
		i = TCMD_Input_string_with_tab("");
		transform (i.begin (), i.end (), i.begin (), toupper);	
		if (i == "")
		{	cout << TAB;		
		}
		if (i != "")
		{	if (i == "R")	// Refreshes the heading. Not sure how useful, but style can be important with these things.
			{	nswitch++;
			}
			if (TCMD_Compare_string(i, "Q") == true)	// Checks for the direct shutdown
			{	DirectExit();	
			}	// The reserved keywords for ending the program. Need to find a reliable way to block these from being used as other menu keywords.	
			else if (TCMD_Compare_string(i, "H") == true)
			{	cout << endl;
				menuhelp();	
			}	// Checks for the menu help command. Essentially just search and output for the keywords of accessible menus 
			else
			{	vector<TCmdMenu*>::iterator Linkit;
				vector<string>::iterator Stringit;
				// Search Down ////////////////////////////////////////////////////////////////////////////////////////////////////
				for (Linkit = (Linkslist.begin()); Linkit != (Linkslist.end()); ++Linkit)	// Search the linkslist (all menus)
				{	for (Stringit = ((*Linkit)->Stringlist.begin()); Stringit != ((*Linkit)->Stringlist.end()); ++Stringit)	// Search the stringlist of each menu
					{	if (*Stringit == this->menuid)
						{	if (i == (*Linkit)->menuid)
							{	cout << NEWLINE << endl;
								(*Linkit)->menu();
							}
						}
					}
				}
				// Search Up //////////////////////////////////////////////////////////////////////////////////////////////////////
				for (Stringit = Stringlist.begin(); Stringit != Stringlist.end(); ++Stringit)
				{	if (i == *Stringit)
					{	for (Linkit = (Linkslist.begin()); Linkit != (Linkslist.end()); ++Linkit)	// Search the linkslist (all menus)
						{	if (i == (*Linkit)->menuid)
							{	cout << NEWLINE << endl;
								(*Linkit)->menu();
							}
							else
							{	goto ExeFunction;	//	Looks around apprehensively. "Are the velociraptors coming?"	:s
							}	
						}
					}
				}
				ExeFunction:
				std::vector<CProgFx*>::iterator Fx_it;
				for (Fx_it = MFxPointers.begin(); Fx_it != MFxPointers.end(); ++Fx_it)
				{	if (i == (*Fx_it)->FxId)
					{	(*Fx_it)->Fx();
						nswitch++;
					}
				}
				cout << NEWLINE;	
			}	
		}	
	}
}
			
			

void TCmdMenu::DirectExit()
{	std::vector<TCmdMenu*>::iterator it;
	std::vector<CProgFx*>::iterator itCP;
	for (it = (Linkslist.begin()); it != (Linkslist.end()); ++it)
	{	for (itCP = (*it)->MFxPointers.begin(); itCP != (*it)->MFxPointers.end(); ++itCP)
		{	delete *itCP;
		}	// Additional cleanup of the function objects assigned to each menu at shutdown time. Not really, really necessary, but good practice nonetheless
		delete *it;
	}	// cleanup time here. Hopefully this works along the lines of what you were thinking ne555?
	ExitCall();		
}	// See ya later


void TCmdMenu::menuhelp()
{	cout << "Enter Q to quit, available commands are: " << NEWLINE << endl;
	vector<TCmdMenu*>::iterator Linkit;
	vector<string>::iterator Stringit;
	for (Linkit = (Linkslist.begin()); Linkit != (Linkslist.end()); ++Linkit)	// Search the linkslist (all menus)
	{	for (Stringit = ((*Linkit)->Stringlist.begin()); Stringit != ((*Linkit)->Stringlist.end()); ++Stringit)	// Search the
		{	if (*Stringit == this->menuid)
			{	cout << (*Linkit)->menuid << endl;
			}
		}
	}
	for (Stringit = Stringlist.begin(); Stringit != Stringlist.end(); ++Stringit)
	{	cout << *Stringit << endl;
	}
	std::vector<CProgFx*>::iterator Fx_it;
	for (Fx_it = MFxPointers.begin(); Fx_it != MFxPointers.end(); ++Fx_it)
	{	cout << (*Fx_it)->FxId << endl;
	}
	cout << endl;
}	//	Oh wont you please, please, help me, help meeeeeeeeeeeeeeeeeeeee


TCmdMenu::~TCmdMenu(void)
{			
}


string TCMD_Input_string_with_tab(string prompt)
{	while(true)
	{	cout << prompt;
		string data;
		cin >> data;
		if (!cin.fail())
		{	return data;
			cout << TAB;		
		}
		cin.clear();
		cin.ignore();
		cout << NEWLINE << NEWLINE;		
	}	
}

int TCMD_Input_int(string prompt)
{	while(true)
	{	cout << prompt;
		int data;
		cin >> data;
		if (!cin.fail())
		{	return data;
			cout << NEWLINE << NEWLINE;	
		}
		cin.clear();
		cin.ignore();
		cout << TAB;	
	}	
}

bool TCMD_Compare_string(string i, string comp)
{	transform (i.begin (), i.end (), i.begin (), toupper);	
	if (i == comp)
	{	return true;	
	}
	else if (i != comp)
	{	return false;	
	}
	else
	{	return false;
	}
}

void ExitCall()
{	cout << "Hail The Probe!!!";
	exit(0);
} 