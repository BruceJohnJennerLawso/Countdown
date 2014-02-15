#include "Time_Structure.h"


Time_Structure::Time_Structure(unsigned int t)
{	this->Set_Time(t);
}

Time_Structure::Time_Structure(unsigned int h, unsigned int m, unsigned int s)
{	this->Set_Time(h, m, s);
}

void Time_Structure::Set_Time(unsigned int h, unsigned int m, unsigned int s)
{	this->time = ((h*3600)+(m*60)+(s*60));
}

void Time_Structure::Set_Time(unsigned int t)
{	this->time = t;
}

void Time_Structure::Zero()
{	this->time = 0;
}

std::string Time_Structure::Get_time_as_string()
{	std::string h = "";
	std::string m = "";
	std::string s = ""; 
	if (((this->Get_hours()) < 10)||((this->Get_minutes()) < 10)||((this->Get_seconds()) < 10))
	{	if((this->Get_hours()) < 10)
		{	h.append("0");
		}
		if((this->Get_minutes()) < 10)
		{	m.append("0");
		}
		if((this->Get_seconds()) < 10)
		{	s.append("0");
		}
	}
	h.append(std::to_string(static_cast<long double>(this->Get_hours())));
	m.append(std::to_string(static_cast<long double>(this->Get_minutes())));
	s.append(std::to_string(static_cast<long double>(this->Get_seconds())));
	return ((((h.append(":")).append(m)).append(":")).append(s));
}

unsigned int Time_Structure::Get_time()
{	return (this->time);
}

unsigned int Time_Structure::Get_hours()
{	unsigned int t = this->Get_time();
	if(t < 3600)
	{	return 0;
	}
	else
	{	unsigned int hours = 0;
		while(t >= 3600)
		{	t -= 3600;
			hours++;
		}	return hours;
	}
}

unsigned int Time_Structure::Get_minutes()
{	unsigned int t = this->Get_time();
	if(t < 60)
	{	return 0;
	}
	else
	{	if((this->Get_hours()) >= 1)
		{	unsigned int hours = this->Get_hours();
			t -= (hours*3600);
			goto minutes_evaluation;
		}
		else
		{	minutes_evaluation:
			unsigned int minutes = 0;
			while(t >= 60)
			{	t -= 60;
				minutes++;
			}	return minutes;
		}
	}
}

unsigned int Time_Structure::Get_seconds()
{	unsigned int t = this->Get_time();
	if(t < 60)
	{	return t;
	}
	else if (t >= 60)
	{	if(t > 3600)
		{	unsigned int hours = this->Get_hours();
			t -= (hours*3600);
			goto minutes_evaluation;
		}
		else if(t == 60)
		{	return 0;
		}
		else
		{	minutes_evaluation:
			while(t >= 60)
			{	t -= 60;
			}
		}
	}
	return t;
}

unsigned int Time_Structure::Get_total_in_seconds()
{	return (this->Get_time());
}

void Time_Structure::Change_by_dt(float dt)
{	unsigned int dt_holder = dt;
	this->time += dt_holder;
}


Time_Structure::~Time_Structure()
{
}
