#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <time.h>
#include <exception>
#include <fstream>
#include <typeinfo>
#define NEWLINE '\n'
#define TAB '\t'
#define VTAB '\v'
#define BEEP '\a'
#define BACK '\b'

namespace Cmd_plusplus	// Currently contains 19 functions! ////////////////////////
{	// Input Functions /////////////////////////////////////////////////////////////
	template <class T> T Input_value(std::string prompt)
	{	while(true)
		{	std::cout << prompt;
			T data;
			std::cin >> data;
			if (!(std::cin.fail()))
			{	return data;	
			}
			std::cin.clear();
			std::cin.ignore();
			std::cout << NEWLINE << NEWLINE;		
		}
	}
	bool Input_bool(std::string prompt);				// Also useful would be an Inputbool that accepted additional true/false identifier strings as arguments to check,
	std::string Input_string(std::string prompt);		// sort of like a "Choose between these input thingies as true or false". 
	// Output Functions ////////////////////////////////////////////////////////////
	void Newline();
	void Newline(int n);
	template<class T> void Print_text(const T out)
	{	std::cout << out;
	}
	std::string Print_text(std::string out);
	template <class T> void Print_text(T out, unsigned int n)
	{	for (unsigned int cy = 0; cy <= n; ++cy)
		{	Cmd_plusplus::Print_text<T>(out);
		}
	}
	template <class T> void Print_line(T out)
	{	std::cout << out << std::endl;
	}
	
	void Print_space();
	void Print_space(unsigned int n);
	// Operator Functions //////////////////////////////////////////////////////////
	int Round_double_to_int (double in);
	std::string Return_Char3_as_String(char i [3]);
	bool Compare_string(std::string i, std::string comp);
	template <class T> T Absolute_value(T val)
	{	if (val >= 0)
		{	return val; 
		}
		else if (val < 0)
		{	val = (0-val);
			return val;
		}
	}
	// Flow Control Functions //////////////////////////////////////////////////////
	int Convert_input_to_integer(std::string i, std::vector<std::string> icomps);
	// General Functions ///////////////////////////////////////////////////////////
	unsigned int GetDTI ();
	std::string Get_date(const char * format);
	
	double Get_epoch_dt();


	std::string Get_directory();
	void Log_exception(std::string e);
	bool Check_file_exists(std::string file_path);
	bool Create_text_file(std::string directory, std::string file_path);
	// System Calls ////////////////////////////////////////////////////////////////
	int Execute_program(std::string application_path);
	#ifdef _WIN32
	void Send_WM_Box(std::string h, std::string m);
	void Send_WM_Box(std::string h, long double m);
	#elif !defined _WIN32
	void Send_WM_Box(std::string h, std::string m);
	void Send_WM_Box(std::string h, long double m);
	#endif
	void ExitCall();
}
