// Alert 1.01 ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "Tree_trunk.h"


#define Program_Title "Alert"
#define Stylechar '-'	

#define Backslash "\""

#define sNULL "NULL"

void Output_program_title(std::string Name);
void InitFxObjects();
void Runprog();


// Function Pointer ids /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace Alert
{	class Alarm_Clock: public CProgFx
	{	public:
		Alarm_Clock(std::string ina){FxId = ina;}
		void Fx();
	};
	class Timer: public CProgFx
	{	public:
		Timer(std::string ina){FxId = ina;}
		void Fx();
	};
	class Check_Time: public CProgFx
	{	public:
		Check_Time(std::string ina){FxId = ina;}
		void Fx();
	};
	CProgFx * Arm_Alarm, * Arm_Timer, * Output_Time;

	std::unique_ptr<TTxt_File> Alarm_list(new TTxt_File(Cmd_plusplus::Get_directory(), "\\Data\\Alarm_list.txt"));
	//TTxt_File * Alarm_list;
};

void InitFxObjects()
{	Alert::Arm_Alarm = new Alert::Alarm_Clock("SET");
	Alert::Output_Time = new Alert::Check_Time("TIME");
	Alert::Arm_Timer = new Alert::Timer("SET");
	// cleaned up when TCmdMenu gets destroyed, no need for manual deallocation :)
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


void Output_program_title(std::string Name)
{	int l = Name.length();
	l = 80 - l;
	double bracketing = l/2;
	l = bracketing;
	std::string Greetings;
	for (int cy = 0; cy <= l; ++cy)
	{	Greetings.insert(Greetings.begin(), Stylechar);
	}
	Greetings.insert(l, Name);
	l = Greetings.length();
	l = 80 - l;
	for (int cy = 0; cy <= l; ++cy)
	{	Greetings.insert(Greetings.end(), Stylechar);
		if (Greetings.length() >= 80)
		{	break;
		}
	}
	std::cout << Greetings << NEWLINE << std::endl;
}	// Works properly now, or so it seems

	
