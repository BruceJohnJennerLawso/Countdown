#include "Functionalize!.h"
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#define NEWLINE '\n'
#define TAB '\t'
#define VTAB '\v'
#define BEEP '\a'
#define BACK '\b'
using namespace std;

// Functionalize! ////////////////////////////////////////////////////////////////////
// Function Library for C++ //////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////
// _________________________________ //
//|	-Functionalize!			   line	|//
//|	  -Input Functions			34	|//
//|	  -Output Functions			82	|//
//|	  -Operator Functions		107	|//
//|	  -Flow Control Functions	148	|//
//|	  -General Functions		167	|//
//|	  -System Call Functions	267	|//
//|_________________________________|//
//									 //
///////////////////////////////////////




// Cmd_plusplus::Input Functions /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

bool Cmd_plusplus::Input_bool(string prompt)
{	while(true)
	{	cout << prompt;
		string data;
		getline (std::cin,data);
		transform (data.begin (), data.end (), data.begin (), toupper);
		if (!cin.fail())
		{	if (((data == "TRUE")||(data == "T"))||(data == "YES"))
			{	cout << NEWLINE << NEWLINE;	
				return true;				
			}
			else if (((data == "FALSE")||(data == "F"))||(data == "NO"))
			{	cout << NEWLINE << NEWLINE;	
				return false;				
			}
			else
			{	cin.clear();
				cin.ignore();
				cout << NEWLINE << NEWLINE;		
			}		
		}
		cin.clear();
		cin.ignore();
		cout << NEWLINE << NEWLINE;		
	}	
}

std::string Cmd_plusplus::Input_string(string prompt)
{	std::string data = "";
	while(true)
	{	cout << endl;
		cout << prompt;
		while(std::getline(std::cin, data))
		{	if (data.size() == 0)
			{	continue;	
			}	
			else
			{	return data;
			}	
		}
	}
}




// Cmd_plusplus::Output Functions ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

std::string Cmd_plusplus::Print_text(std::string out)
{	std::cout << out;
	return out;
}

void Cmd_plusplus::Newline()
{	cout << "\n";
}

void Cmd_plusplus::Newline(int n)
{	for(int cy = 0; cy <= n; ++cy)
	{	Cmd_plusplus::Newline();
	}	// So, like call your overloaded relative function...
}	// Kinda cool in a way

void Cmd_plusplus::Print_space()
{	cout << " ";
}

void Cmd_plusplus::Print_space(unsigned int n)
{	for (unsigned int cy = 0; cy <= n; ++cy)
	{	Cmd_plusplus::Print_space();	
	}
}




// Cmd_plusplus::Data operator functions /////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

int Cmd_plusplus::Round_double_to_int (double in)
{	int d;
	d = in;
	in = in - d;
	if (in == 0.5)
	{	return d;	
	}	// I couldnt decide dammit!
	else if (in > 0.5)
	{	d++;
		return d;	
	}
	else if (in < 0.5)
	{	return d;	
	}
}

string Cmd_plusplus::Return_Char3_as_String(char i [3])
{	string output;
	output = "";
	output.insert (output.end(), 1, i [2]);
	output.insert (output.end(), 1, i [1]); 
	output.insert (output.end(), 1, i [0]);
	return output;							
}

bool Cmd_plusplus::Compare_string(string i, string comp)
{	transform (i.begin (), i.end (), i.begin (), toupper);	
	if (i == comp)
	{	return true;	
	}
	else if (i != comp)
	{	return false;	
	}		
}




// Cmd_plusplus::Program flow control functions //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

int Cmd_plusplus::Convert_input_to_integer(std::string i, std::vector<std::string> icomps)
{	std::vector<std::string>::iterator itString;
	unsigned int n = 0;
	for(itString = icomps.begin(); itString != icomps.end(); ++itString)
	{	n++;
		if (*itString == i)
		{	icomps.clear();		// String Vector is cleared for you if a hit is registered, but not...
			return n;			// No idea what the last comment was supposed to mean... sorry :p
		}						// It helps if you comment while the idea is still fresh in your mind.
	}
	return 0;
}




// Cmd_plusplus::General Functions ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN64
    #include <direct.h>
    #define GetCurrentDir _getcwd
	void Cmd_plusplus::
#elif _WIN32
    #include <direct.h>
	#include <windows.h>
    #define GetCurrentDir _getcwd
	int Cmd_plusplus::Execute_program(std::string application_path)
	{	LPCTSTR lpApplicationName = application_path.c_str(); /* The program to be executed */
		LPSTARTUPINFO lpStartupInfo;
		LPPROCESS_INFORMATION lpProcessInfo;
		memset(&lpStartupInfo, 0, sizeof(lpStartupInfo));
		memset(&lpProcessInfo, 0, sizeof(lpProcessInfo));
		if (!CreateProcess(lpApplicationName,NULL, NULL, NULL,NULL, NULL, NULL, NULL,lpStartupInfo,lpProcessInfo))
		{	std::cerr <<  lpApplicationName << " Has failed to start" << "\"\n";
			return -1;
		}
		return 0;
	}
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
		#include <unistd.h>
		#define GetCurrentDir getcwd
    #elif TARGET_OS_IPHONE
        #include <unistd.h>
		#define GetCurrentDir getcwd
    #elif TARGET_OS_MAC
        #include <unistd.h>
		#define GetCurrentDir getcwd
    #else
        #include <unistd.h>
		#define GetCurrentDir getcwd
    #endif
#elif __linux
    #include <unistd.h>
    #define GetCurrentDir getcwd
	int Cmd_plusplus::Execute_program(std::string application_path)
	{	char* programPath = application_path;
		pid_t pid = fork(); /* Create a child process */
		switch (pid) 
		{	case -1: /* Error */
			return -1;
			case 0: /* Child process */
			execl(programPath, NULL); /* Execute the program */
			return -2;
			default: /* Parent process */
			std::cout << "Process created with pid " << pid << "\n";
			int status;
			while (!WIFEXITED(status)) 
			{	waitpid(pid, status, 0); /* Wait for the process to complete */
			}
			return 0;
		}
	}
#elif __unix // all unices not caught above
    #include <unistd.h>
    #define GetCurrentDir getcwd
	int Cmd_plusplus::Execute_program(std::string application_path)
	{	char* programPath = application_path;
		pid_t pid = fork(); /* Create a child process */
		switch (pid) 
		{	case -1: /* Error */
			return -1;
			case 0: /* Child process */
			execl(programPath, NULL); /* Execute the program */
			return -2;
			default: /* Parent process */
			std::cout << "Process created with pid " << pid << "\n";
			int status;
			while (!WIFEXITED(status)) 
			{	waitpid(pid, status, 0); /* Wait for the process to complete */
			}
			return 0;
		}
	}
#elif __posix
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif


std::string Cmd_plusplus::Get_directory()
{	char cCurrentPath[FILENAME_MAX];
	std::string Directory;
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {	Directory = "NOPATH";
		return Directory;
    }
	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; // not really required
	Directory = cCurrentPath;
	return Directory;
}

std::string Cmd_plusplus::Get_date(const char * format)
{	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];	
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime (buffer, 80, format, timeinfo);	
	std::string number = buffer;	
	return number;	// Need to convert string to integer... yeah... This was finished sometime... Apparently...
}

double Cmd_plusplus::Get_epoch_dt ()
{	time_t timer;
	struct tm y2k;
	double seconds;
	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
	time(&timer);
	seconds = difftime(timer,mktime(&y2k));
	return seconds;										
}

unsigned int Cmd_plusplus::GetDTI ()
{	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];	
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime (buffer, 80, "%d%m%y", timeinfo);	
	std::string number = buffer;	
	unsigned int DTI = std::stoi(number);
	return DTI;	// Need to convert string to integer... yeah... This was finished sometime... Apparently...
}

void Cmd_plusplus::Log_exception(std::string e)
{	std::ofstream errorfile("error.txt");
	if (errorfile.is_open())
	{	errorfile << Cmd_plusplus::GetDTI() << "__" << e << "Endlog\n";
		errorfile.close();
	}
}

bool Cmd_plusplus::Check_file_exists(std::string file_path)
{	bool Check_return = false;
	ifstream file (file_path);
	if(file.is_open())
	{	Check_return = true;
	}	file.close();
	return Check_return;
}

bool Cmd_plusplus::Create_text_file(std::string directory, std::string file_path)
{	switch(Check_file_exists(directory.append(file_path)))	// Please note, your input has to be complete, including the .txt file extension
	{	case true:
		return false;
		case false:
		ofstream file (directory);
		if (file.is_open())
		{	file << "//Cmd_plusplus generated file\n" << "//Created on " << Cmd_plusplus::GetDTI(); 
		}
		file.close();
		return true;
	}
	return false;
}




// Cmd_plusplus::System Call Fuctions ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#include <windows.h>
void Cmd_plusplus::Send_WM_Box (std::string h, std::string m)
{	MessageBox(NULL, m.c_str(), h.c_str(), MB_OK);
}	//OS Windows Specific function for sending a message box from inside the command line. Unusual, but somewhat interesting I guess
void Cmd_plusplus::Send_WM_Box(std::string h, long double m)
{	string i;
	i = std::to_string(m);
	MessageBox(NULL, i.c_str() , h.c_str(), MB_OK);
}
#elif !defined _WIN32
void Send_WM_Box (std::string h, std::string m)
{	cout << NEWLINE << "Please note: Send_WM_Box is only available with a Win32 compatible compiler" << NEWLINE;
}
void Send_WM_Box(std::string h, long double m)
{	cout << NEWLINE << "Please note: Send_WM_Box is only available with a Win32 compatible compiler" << NEWLINE;
}
#endif

void Cmd_plusplus::ExitCall()
{	cout << "Hail The Probe!!!";
	exit(0);
} 




// Functionalize! By John Lawson /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////



//	Hail the Probe!!!

