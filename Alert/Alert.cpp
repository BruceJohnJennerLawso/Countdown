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
	(timer)->Embed_function(Alert::Arm_Timer);
	(main)->Embed_function(Alert::Output_Time);
	(main)->menu();	// The equivalent of hundreds of lines of i/o code, neatly packaged into a few lines <3				
}

void Alert::Alarm_Clock::Fx()
{	unsigned int Timerlength = Cmd_plusplus::Input_value<unsigned int>("Length of timer: ");
	TTxt_File Args(Cmd_plusplus::Get_directory(), "\\Countdown\\CountdownArgs.txt");
	Args.Overwrite_data((std::to_string(static_cast<long double>(Timerlength))), 1);
	Args.Overwrite_data("Alarm10.ogg", 2);
	Args.Save_file(Args.Get_path(), true);
	WinExec((Cmd_plusplus::Get_directory()).append("\\Countdown\\Countdown.exe").c_str(),SW_SHOW);
}

void Alert::Timer::Fx()
{	unsigned int Timerlength = Cmd_plusplus::Input_value<unsigned int>("Length of timer: ");
	TTxt_File Args(Cmd_plusplus::Get_directory(), "\\Countdown\\CountdownArgs.txt");
	Args.Overwrite_data((std::to_string(static_cast<long double>(Timerlength))), 1);
	Args.Overwrite_data("ElapsedTimer.ogg", 2);
	Args.Save_file(Args.Get_path(), true);
	WinExec((Cmd_plusplus::Get_directory()).append("\\Countdown\\Countdown.exe").c_str(),SW_SHOW);
}


void Alert::Check_Time::Fx()
{	Cmd_plusplus::Newline();
	Cmd_plusplus::Print_line(Cmd_plusplus::Get_date("%X %d.%m.%Y"));
}



// Old Alarm Code //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

