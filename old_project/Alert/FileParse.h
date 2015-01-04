#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <time.h>
#include <algorithm>
#include "Functionalize!.h"


class CFileParse
{	public:
	CFileParse(void);
	virtual void Load_file();
	virtual void Save_file();
	virtual ~CFileParse(void);
};

namespace Parse_functions
{	void Log_exception(std::string e);
	unsigned int GetDTI ();
	std::string Get_directory();
};

#ifdef _WIN64
    #include <direct.h>
    #define GetCurrentDir _getcwd
#elif _WIN32
    #include <direct.h>
    #define GetCurrentDir _getcwd
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
#elif __unix // all unices not caught above
    #include <unistd.h>
    #define GetCurrentDir getcwd
#elif __posix
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

