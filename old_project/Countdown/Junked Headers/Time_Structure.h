#pragma once
#include <string>

class Time_Structure
{	public:
	Time_Structure(unsigned int t);
	Time_Structure(unsigned int h, unsigned int m, unsigned int s);
	void Set_Time(unsigned int h, unsigned int m, unsigned int s);
	void Set_Time(unsigned int t);
	void Zero();
	std::string Get_time_as_string();
	unsigned int Get_time();
	unsigned int Get_hours();
	unsigned int Get_minutes();
	unsigned int Get_seconds();
	unsigned int Get_total_in_seconds();
	void Change_by_dt(float dt);
	int time;			// Total time in seconds
	~Time_Structure();
};

