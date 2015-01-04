#pragma once
#include "GenericMenu.h"
#include <iostream>
#include <string>
#include <vector>
#define NEWLINE '\n'
#define TAB '\t'
#define VTAB '\v'
#define BEEP '\a'
#define BACK '\b'




class TCmdMenu :public CGenericMenu
{	public:
	TCmdMenu(void);
	void menu();
	void menuhelp();
	TCmdMenu(std::string menu_id, std::string menu_name);
	TCmdMenu(std::string above_menu, std::string menu_id, std::string menu_name);
	int Execute_By_Id(std::string function_link_name);
	std::vector<std::string> Stringlist;
	void DirectExit();
	~TCmdMenu(void);
};

