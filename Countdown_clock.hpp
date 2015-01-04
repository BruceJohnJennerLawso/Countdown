// Countdown_clock.hpp /////////////////////////////////////////////////////////
// A wrapper for the countdown clock ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//#include <std_files>
//#include "Headers.h"
//#include "Headers.hpp"
//#include "Source.cpp"
#include "SFML_Button.hpp"

#ifndef countdownclockH
#define countdownclockH

enum countdown_mode{clock_mode, timer_mode};

enum timer_status{paused, running};


class Countdown_clock
{	public:
	Countdown_clock(unsigned int initial_time, sf::Color theme_colour, timer_status initial_status, std::string font_path, sf::Texture &go_texture, sf::Texture &pow_texture, std::string alert_path);
	// implicitly a countdown timer here
	Countdown_clock(sf::Color theme_colour, std::string font_path, sf::Texture &pow_texture);
	// and again, implicitly a clock here, based on the arguments it is given
	countdown_mode Mode;
	double deltat;
	// length of the frame
	
	SFML_Window * Countdown_window;
	Cursor_commands * cursor_commands;
	
	SFML_Button * Go_button, * Power_button;
	sf::Font Display_font;
	SFML_text * Display_text;
	
	timer_status Countdown_status;
	Time_Structure * Current_time;
	
	std::string Alert_path;
	
	void Alert();
	
	sf::Music music;
	
	int Countdown();
	int Countdown(unsigned int countdown_time);
	
	int Clock();
	
	~Countdown_clock();
};

std::string Get_clock_time_as_string();

#endif
