// Alert /////////////////////////////////////////////////////////////////
// Time application written in C++ ///////////////////////////////////////
// Warranty void if used in the TARDIS ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#include <time.h>
#include <math.h>
#include <windows.h>
#include <mmsystem.h>
#include "ProgData.h"



int main ()
{	try
	{	Output_program_title(Program_Title);
		Runprog();
	}
	catch(char* e)
	{	Cmd_plusplus::Log_exception(e);
		return 0;
	}	
}

void Runprog()
{	InitFxObjects();
	CGenericMenu * main = new TCmdMenu ("MAIN", "Main-Menu");
	CGenericMenu * alarm = new TCmdMenu ("MAIN", "ALARM", "Alarm Menu");
	CGenericMenu * timer = new TCmdMenu ("MAIN", "TIMER", "Timer Menu");
	(alarm)->Embed_function(Alert::Arm_Alarm);
	(alarm)->Embed_function(Alert::Set_Alarm_Audio);
	(timer)->Embed_function(Alert::Arm_Timer);
	(timer)->Embed_function(Alert::Set_Timer_Audio);
	(main)->Embed_function(Alert::Output_Time);
	(main)->Embed_function(Alert::Colour_Config);
	(main)->menu();	// The equivalent of hundreds of lines of i/o code, neatly packaged into a few lines <3				
}

void Alert::Set_Colour::Fx()
{	while(true)
	{	std::string icolour = Cmd_plusplus::Input_string("Colour for Countdown clock: ");
		std::transform(icolour.begin(), icolour.end(), icolour.begin(), toupper);
		if((icolour == "BLUE")||(icolour == "MAGENTA")||(icolour == "CYAN")||(icolour == "GREEN")||(icolour == "RED")||(icolour == "YELLOW"))
		{	TTxt_File Arguments(Cmd_plusplus::Get_directory(), "\\Countdown\\CountdownArguments.cfg");
			Arguments.Overwrite_data(icolour, 5);
			Arguments.Save_file(Arguments.Get_path(), true);
			break;
		}
		else if((icolour == "H")||(icolour == "HELP"))
		{	Cmd_plusplus::Print_line("Enter a colour for the Countdown clock UI, or 'Q' to cancel");
			Cmd_plusplus::Newline();
			Cmd_plusplus::Print_line("Available colours are: ");
			Cmd_plusplus::Print_line("Blue");
			Cmd_plusplus::Print_line("Green");
			Cmd_plusplus::Print_line("Magenta");
			Cmd_plusplus::Print_line("Cyan");
			Cmd_plusplus::Print_line("Red");
			Cmd_plusplus::Print_line("Yellow");
		}
		else if(icolour == "Q")
		{	break;
		}
		else
		{	Cmd_plusplus::Print_line("Invalid colour. Enter 'H' for the list of currently available colours");
		}
	}
}

void Alert::Alarm_Clock::Fx()
{	unsigned int Timerlength = Alert::Get_time_as_hhmmss();
	TTxt_File Arguments(Cmd_plusplus::Get_directory(), "\\Countdown\\CountdownArguments.cfg");
	Arguments.Overwrite_data((std::to_string(static_cast<long double>(Timerlength))), 1);
	Arguments.Overwrite_data("Alarm", 2);
	Arguments.Save_file(Arguments.Get_path(), true);
	WinExec((Cmd_plusplus::Get_directory()).append("\\Countdown\\Countdown.exe").c_str(),SW_SHOW);
}

void Alert::Set_Alarm_Sound::Fx()
{	std::string Filename = Cmd_plusplus::Input_string("Name of Audio file: ");
	if((Filename != "Q")&&(Filename.size() != 0))
	{	TTxt_File Arguments(Cmd_plusplus::Get_directory(), "\\Countdown\\CountdownArguments.cfg");
		Arguments.Overwrite_data(Filename, 4);
		Arguments.Save_file(Arguments.Get_path(), true);
	}
	else
	{	
	}
}

void Alert::Timer::Fx()
{	unsigned int Timerlength = Alert::Get_time_as_hhmmss();
	TTxt_File Arguments(Cmd_plusplus::Get_directory(), "\\Countdown\\CountdownArguments.cfg");
	Arguments.Overwrite_data((std::to_string(static_cast<long double>(Timerlength))), 1);
	Arguments.Overwrite_data("Timer", 2);
	Arguments.Save_file(Arguments.Get_path(), true);
	WinExec((Cmd_plusplus::Get_directory()).append("\\Countdown\\Countdown.exe").c_str(),SW_SHOW);
}

void Alert::Set_Timer_Sound::Fx()
{	std::string Filename = Cmd_plusplus::Input_string("Name of Audio file: ");
	if((Filename != "Q")&&(Filename.size() != 0))
	{	TTxt_File Arguments(Cmd_plusplus::Get_directory(), "\\Countdown\\CountdownArguments.cfg");
		Arguments.Overwrite_data(Filename, 3);
		Arguments.Save_file(Arguments.Get_path(), true);
	}
	else
	{	
	}
}

unsigned int Alert::Get_time_as_hhmmss()
{	unsigned int hours, minutes, seconds, time;
	time = 0;
	Cmd_plusplus::Print_line("Please input time to run: ");
	Cmd_plusplus::Newline();
	while(true)
	{	hours = Cmd_plusplus::Input_value<unsigned int>("Hours: ");
		if(hours <= 99)
		{	break;
		}
		else
		{	Cmd_plusplus::Print_line("Value too large. Please input a smaller number.");
		}	
	}	time += (hours*3600);
	while(true)
	{	minutes = Cmd_plusplus::Input_value<unsigned int>("Minutes: ");
		if(minutes <= 59)
		{	break;
		}
		else
		{	Cmd_plusplus::Print_line("Value too large. Please input a smaller number.");
		}	
	}	time += (minutes*60);
	while(true)
	{	seconds = Cmd_plusplus::Input_value<unsigned int>("Seconds: ");
		if(seconds <= 59)
		{	break;
		}
		else
		{	Cmd_plusplus::Print_line("Value too large. Please input a smaller number.");
		}	
	}	time += (seconds);
	return time;
}

void Alert::Check_Time::Fx()
{	Cmd_plusplus::Newline();
	Cmd_plusplus::Print_line(Cmd_plusplus::Get_date("%X %d.%m.%Y"));
}



// Old Alarm Code //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

