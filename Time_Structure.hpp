#pragma once
#include <string>

#ifndef time_struc
#define time_struc



class Time_Structure
{	public:
	Time_Structure(unsigned long int t);
	Time_Structure(unsigned long int h, unsigned long int m, unsigned long int s);
	void Set_Time(unsigned long int h, unsigned long int m, unsigned long int s);
	void Set_Time(unsigned long int t);
	void Zero();
	std::string Get_time_as_string();
	unsigned long int Get_time();
	unsigned long int Get_hours();
	unsigned long int Get_minutes();
	unsigned long int Get_seconds();
	unsigned long int Get_total_in_seconds();
	void Change_by_dt(long double dt);
	long double time;			// Total time in seconds
	~Time_Structure();
};

#endif
